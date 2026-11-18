"""Release canary for the free-threaded wheel build.

Run against an installed wheel on a free-threaded interpreter:
    python test/wheel_canary.py

Checks, in order:
1. this is really a free-threaded build and importing simplejpeg does not
   re-enable the GIL (import canary)
2. buffer exports are released after the call (post-call resize stays
   clean, raised BufferError otherwise)
3. child-process stress session (segfault-proof, exit-code watched):
   decode/encode/header/yuv pipelines raced on threads with byte-exact
   results, all documented error paths raised concurrently,
   buffer-resize refusals in both directions, reference-count churn of
   output temporaries plus a gc.collect() free-rider thread

Exit 0 = pass. Used by the release workflow against the built wheel.
"""

import os
import subprocess
import sys
import sysconfig
import threading
import time
import traceback
from collections import Counter

WIDTH = 512
HEIGHT = 384
BIG_DIM = 1536
JOIN_TIMEOUT = 120.0
RACE_SECONDS = 2.5
BUDGET = 1.5  # per-scenario wall budget for the pipeline groups


OPS = Counter()
RESIZES = Counter()
ERRORS = []
RESULTS_FAIL = []
LOCK = threading.Lock()


def _note(key):
    with LOCK:
        OPS[key] += 1


def _random_bytes(seed, count):
    data = bytearray(count)
    state = seed & 0xFFFFFFFFFFFFFFFF
    top = 0xFFFFFFFFFFFFFFFF
    for index in range(count):
        state = (state * 6364136223846793005 + 1442695040888963407) & top
        data[index] = (state >> 33) & 0xFF
    return bytes(data)


def check_build_and_import():
    gil_disabled = sysconfig.get_config_var('Py_GIL_DISABLED')
    assert gil_disabled == 1, (
        'not a free-threaded build: Py_GIL_DISABLED = %r' % (gil_disabled,))
    assert 'free-threading build' in sys.version, (
        'not a free-threaded build: %r' % sys.version)
    import numpy
    import simplejpeg
    assert sys._is_gil_enabled() is False, 'the GIL is enabled after import'
    module_dir = os.path.dirname(simplejpeg.__file__)
    assert 'site-packages' in module_dir, (
        'simplejpeg not imported from site-packages: %s' % simplejpeg.__file__)
    print('canary: free-threaded build ok, GIL off after import, '
          'simplejpeg %s (numpy %s) from %s'
          % (simplejpeg.__version__, numpy.__version__, module_dir))


def build_fixtures():
    import numpy as np
    import simplejpeg

    def image(width, height, channels):
        count = width * height * channels
        flat = np.frombuffer(_random_bytes(count, count), np.uint8)
        return flat.reshape(height, width, channels).copy()

    fixtures = {'simplejpeg': simplejpeg}
    fixtures['image'] = image(WIDTH, HEIGHT, 3)
    fixtures['image_gray'] = image(WIDTH, HEIGHT, 1)
    fixtures['image_big'] = image(BIG_DIM, BIG_DIM, 3)
    y = image(WIDTH, HEIGHT, 1)[:, :, 0].copy()
    u = image(WIDTH // 2, HEIGHT // 2, 1)[:, :, 0].copy()
    fixtures['planes'] = (y, u, u.copy())

    enc = fixtures['enc'] = {}
    enc['main'] = simplejpeg.encode_jpeg(fixtures['image'])
    enc['fast'] = simplejpeg.encode_jpeg(fixtures['image'], fastdct=True)
    enc['gray'] = simplejpeg.encode_jpeg(
        fixtures['image_gray'], colorspace='gray', colorsubsampling='gray')
    enc['yuv'] = simplejpeg.encode_jpeg_yuv_planes(*fixtures['planes'])
    enc['gray_yuv'] = simplejpeg.encode_jpeg_yuv_planes(y, None, None)
    enc['big'] = simplejpeg.encode_jpeg(fixtures['image_big'])

    dec = fixtures['dec'] = {}
    dec['rgb'] = simplejpeg.decode_jpeg(enc['main'])
    dec['gray'] = simplejpeg.decode_jpeg(enc['main'], colorspace='gray')
    dec['fast'] = simplejpeg.decode_jpeg(enc['fast'], fastdct=True)
    dec['yuv'] = simplejpeg.decode_jpeg(enc['yuv'])
    dec['big'] = simplejpeg.decode_jpeg(enc['big'])

    fixtures['header'] = simplejpeg.decode_jpeg_header(enc['main'])
    fixtures['snapshots'] = {
        'image': fixtures['image'].copy(),
        'jpeg_main': bytes(enc['main']),
        'jpeg_yuv': bytes(enc['yuv']),
    }
    return fixtures


# ---- race-free pipeline sections: exact results on every call --------------

def make_decode_check(fixtures, jpeg, reference, **options):
    import numpy as np
    simplejpeg = fixtures['simplejpeg']

    def check():
        result = simplejpeg.decode_jpeg(jpeg, **options)
        if not np.array_equal(result, reference):
            raise AssertionError('decoded bytes differ from the reference')

    return check


def make_encode_check(fixtures, image, **options):
    simplejpeg = fixtures['simplejpeg']
    reference = simplejpeg.encode_jpeg(image, **options)

    def check():
        if simplejpeg.encode_jpeg(image, **options) != reference:
            raise AssertionError('encoded bytes differ from the reference')

    return check


def make_header_check(fixtures, jpeg, reference):
    simplejpeg = fixtures['simplejpeg']

    def check():
        if simplejpeg.decode_jpeg_header(jpeg) != reference:
            raise AssertionError('header differs from the reference')

    return check


def make_error_check(fixtures):
    import numpy as np
    simplejpeg = fixtures['simplejpeg']
    image = fixtures['image']
    too_small = bytearray(96)
    garbage = _random_bytes(4096, 4096)
    truncated = bytes(fixtures['enc']['main'][:-32])
    flipped = np.flipud(image)
    channels_wrong = np.resize(image, (HEIGHT, WIDTH, 2))
    y, u, v = fixtures['planes']
    two_planes = (y, u, None)
    other_plane_missing = (y, None, v)
    oversized_u = np.resize(u, (HEIGHT, WIDTH))
    expected = [
        (lambda: simplejpeg.decode_jpeg(garbage), 'JPEG'),
        # a trimmed file can fail with different libjpeg messages,
        # only the ValueError type assertion applies
        (lambda: simplejpeg.decode_jpeg(truncated), None),
        (
            lambda: simplejpeg.decode_jpeg(
                fixtures['enc']['main'],
                buffer=bytearray(too_small),
            ),
            'too small',
        ),
        (
            lambda: simplejpeg.encode_jpeg(channels_wrong),
            'channels does not match',
        ),
        (lambda: simplejpeg.encode_jpeg(flipped), None),
        (
            lambda: simplejpeg.encode_jpeg_yuv_planes(*two_planes),
            'V (missing)',
        ),
        (
            lambda: simplejpeg.encode_jpeg_yuv_planes(*other_plane_missing),
            'U (missing)',
        ),
        (
            lambda: simplejpeg.encode_jpeg_yuv_planes(y, oversized_u, v),
            'U and V planes must have matching shape',
        ),
    ]

    def check():
        for function, message in expected:
            try:
                function()
            except ValueError as e:
                if message is not None and message not in str(e):
                    raise AssertionError(
                        'unexpected error message: %r' % str(e)) from e
            except BaseException as e:
                raise AssertionError(
                    'unexpected %r raised: %r' % (type(e), str(e))) from e
            else:
                raise AssertionError(
                    'expected error %r was not raised'
                    % (message if message is not None else 'ValueError',
                       ))
            _note('expected error')

    return check


# ---- resize races: refusals are the expected outcome, decode stays correct --

def run_resize_races(fixtures, stop, live):
    import numpy as np
    simplejpeg = fixtures['simplejpeg']
    jpeg_big = fixtures['enc']['big']
    reference_big = fixtures['dec']['big']
    needed = reference_big.nbytes

    def output_pair(index):
        buf = bytearray(needed)

        def decoder():
            while not stop.is_set():
                try:
                    result = simplejpeg.decode_jpeg(jpeg_big, buffer=buf)
                    if not np.array_equal(result, reference_big):
                        with LOCK:
                            RESULTS_FAIL.append('output resize decode')
                        stop.set()
                        return
                    with LOCK:
                        RESIZES['output decodes ok'] += 1
                except BaseException:
                    with LOCK:
                        ERRORS.append(
                            ('output decoder', traceback.format_exc()))
                    stop.set()
                    return

        def resizer():
            while not stop.is_set():
                try:
                    del buf[-1:]
                    buf.extend(b'\x00')
                except BufferError:
                    with LOCK:
                        RESIZES['output resize refused'] += 1
                time.sleep(0.001)

        for target in (decoder, resizer):
            thread = threading.Thread(
                target=target, name='output-race-%d' % index)
            thread.start()
            live.append(thread)

    def input_pair(index):
        buf = bytearray(jpeg_big)

        def decoder():
            while not stop.is_set():
                try:
                    simplejpeg.decode_jpeg(buf)
                    with LOCK:
                        RESIZES['input decodes ok'] += 1
                except ValueError:
                    # a trim can slip in between two decodes: a shortened
                    # bytearray is then a broken input, a documented
                    # user error handled by ValueError
                    with LOCK:
                        RESIZES['input shortened -> ValueError'] += 1
                except BufferError:
                    with LOCK:
                        RESIZES['input resize refused'] += 1
                except BaseException:
                    with LOCK:
                        ERRORS.append(
                            ('input decoder', traceback.format_exc()))
                    stop.set()
                    return

        def resizer():
            while not stop.is_set():
                try:
                    del buf[-1:]
                    buf.extend(b'\x00')
                except BufferError:
                    with LOCK:
                        RESIZES['input resize refused'] += 1
                time.sleep(0.001)

        for target in (decoder, resizer):
            thread = threading.Thread(
                target=target, name='input-race-%d' % index)
            thread.start()
            live.append(thread)

    return output_pair, input_pair


def gc_free_rider(stop):
    import gc
    while not stop.is_set():
        gc.collect()
        time.sleep(0.02)


def storm_child():
    assert sys._is_gil_enabled() is False, 'the GIL is enabled'
    fixtures = build_fixtures()
    simplejpeg = fixtures['simplejpeg']
    enc = fixtures['enc']
    dec = fixtures['dec']
    threads = int(os.environ.get('CANARY_THREADS', str(os.process_cpu_count())))

    def calibrated(check):
        check()  # warmup: first call carries one-time init cost
        start = time.perf_counter()
        check()
        duration = time.perf_counter() - start
        iters = max(4, min(int(BUDGET / max(duration, 1e-6)), 5000))
        return iters, duration

    y, u, v = fixtures['planes']
    yuv_reference = simplejpeg.encode_jpeg_yuv_planes(y, u, v)
    gray_yuv_reference = simplejpeg.encode_jpeg_yuv_planes(y, None, None)

    def yuv_check():
        if simplejpeg.encode_jpeg_yuv_planes(y, u, v) != yuv_reference:
            raise AssertionError('yuv bytes differ from the reference')
        if simplejpeg.encode_jpeg_yuv_planes(y, None, None) \
                != gray_yuv_reference:
            raise AssertionError('gray bytes differ from the reference')

    groups = [
        ('decode rgb', make_decode_check(fixtures, enc['main'], dec['rgb'])),
        ('decode gray', make_decode_check(
            fixtures, enc['main'], dec['gray'], colorspace='gray')),
        ('decode fastdct',
         make_decode_check(fixtures, enc['fast'], dec['fast'],
                           fastdct=True)),
        ('decode yuv', make_decode_check(fixtures, enc['yuv'], dec['yuv'])),
        ('encode main', make_encode_check(fixtures, fixtures['image'])),
        ('encode fastdct',
         make_encode_check(fixtures, fixtures['image'], fastdct=True)),
        ('encode gray', make_encode_check(
            fixtures, fixtures['image_gray'],
            colorspace='gray', colorsubsampling='gray')),
        ('encode yuv', yuv_check),
        ('header', make_header_check(
            fixtures, enc['main'], fixtures['header'])),
        ('error paths', make_error_check(fixtures)),
    ]

    live = []
    stop = threading.Event()
    print('threads: %d' % threads)
    for name, check in groups:
        iters, duration = calibrated(check)
        print('calibrated %-14s %6.1f ms -> %d iters'
              % (name, duration * 1000, iters))

        def runner(function=check, iterations=iters, group=name):
            try:
                for _ in range(iterations):
                    function()
                _note(group)
            except BaseException:
                with LOCK:
                    ERRORS.append((group, traceback.format_exc()))

        for i in range(threads):
            thread = threading.Thread(target=runner,
                                      name='%s-%d' % (name, i))
            thread.start()
            live.append(thread)

    gc_thread = threading.Thread(
        target=gc_free_rider, args=(stop,), name='gc')
    gc_thread.start()
    live.append(gc_thread)

    output_pair, input_pair = run_resize_races(fixtures, stop, live)
    units = max(1, threads // 2) if threads > 1 else 1
    for index in range(units):
        output_pair(index)
    for index in range(2 if threads > 1 else 1):
        input_pair(index)

    time.sleep(RACE_SECONDS)
    stop.set()
    for thread in live:
        thread.join(timeout=JOIN_TIMEOUT)
    alive = [t.name for t in live if t.is_alive()]

    # ---- integrity after the storm ----
    import numpy as np
    image_ok = np.array_equal(fixtures['image'], fixtures['snapshots']['image'])
    bytes_ok = (bytes(enc['main']) == fixtures['snapshots']['jpeg_main']
                and bytes(enc['yuv']) == fixtures['snapshots']['jpeg_yuv'])
    refusals = (RESIZES['output resize refused']
                + RESIZES['input resize refused'])
    refusals_ok = threads < 2 or refusals > 0

    print('\nops:', dict(OPS))
    print('resize races:', dict(RESIZES))
    for group, tb in ERRORS[:5]:
        print('--- unexpected error in %s ---\n%s' % (group, tb))
    if RESULTS_FAIL:
        print('WRONG RESULTS: %r' % RESULTS_FAIL[:5])
    if alive:
        print('HUNG THREADS: %r' % alive[:10])
    if not image_ok or not bytes_ok:
        print('INTEGRITY FAIL after storm')
    if not refusals_ok:
        print('no buffer-resize refusals observed with %d threads '
              '(expected refusals under contention)' % threads)

    ok = (image_ok and bytes_ok and not alive and not ERRORS
          and not RESULTS_FAIL and refusals_ok)
    print('STORM %s' % ('PASS' if ok else 'FAIL'))
    return 0 if ok else 1


def exports_released_check():
    import numpy as np
    import simplejpeg
    image = np.frombuffer(
        _random_bytes(64 * 64 * 3, 64 * 64 * 3), np.uint8).reshape(
        64, 64, 3).copy()
    jpeg = simplejpeg.encode_jpeg(image)
    height, width = simplejpeg.decode_jpeg_header(jpeg)[:2]
    buf = bytearray(height * width * 3 + 16)
    simplejpeg.decode_jpeg(jpeg, buffer=buf)
    buf += b'x' * 8  # BufferError here would mean a leaked export
    print('canary: buffer exports fully released after decode')


def main():
    if '--child-storm' in sys.argv:
        sys.exit(storm_child())
    check_build_and_import()
    exports_released_check()
    print('canary: starting child-process storm ...')
    finished = subprocess.run(
        [sys.executable, os.path.abspath(__file__), '--child-storm'],
        stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True,
        timeout=900,
    )
    print(finished.stdout[-6000:])
    if finished.returncode != 0:
        print('canary: storm child failed with exit code %d'
              % finished.returncode, file=sys.stderr)
        sys.exit(1)
    print('canary: storm ok')
    sys.exit(0)


if __name__ == '__main__':
    main()
