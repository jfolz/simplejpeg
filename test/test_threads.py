"""
Free-threaded concurrency storm as plain tests.

Every documented entry point is hammered from many worker threads whose
byte-exact results must replicate, all documented error paths are raised
concurrently, bytearray resizes race the buffer protocol around decodes
in both directions, and a background gc.collect() rider frees output
temporaries out from under the workers. As suite tests the storm runs on
every free-threaded leg of the wheel matrix, so a release cannot go out
without the concurrent-use exercise on free-threaded interpreters.

The tests are marked ``free_threaded``: on GIL builds the run order is
forced serial, the races lose their signal and only burn CI time, so the
shared conftest gate skips them there. Runtime knobs for constrained
environments (the ASan workflow sets STORM_BUDGET to shrink the storm):

- ``STORM_BUDGET``: wall window per group and per race, default 1.0 s
- ``STORM_THREADS``: hard override of the storm thread count
"""

import gc
import os
import sys
import threading
import time
import traceback

import numpy as np
import pytest
from harness import generate_image

import simplejpeg

WIDTH = 512
HEIGHT = 384
JOIN_TIMEOUT = 60.0

BUDGET = float(os.environ.get('STORM_BUDGET', '1.0'))


def _thread_count():
    override = os.environ.get('STORM_THREADS')
    if override:
        return max(1, int(override))
    cpu_count = getattr(os, 'process_cpu_count', os.cpu_count)()
    return max(2, min(cpu_count, 8))


class _Storm:
    """
    Pool of racing daemon threads under one shared stop event: batch
    members run a finite loop and leave on their own, race members
    loop until the stop fires. Every unexpected exception is collected
    as ``(name, traceback)`` and releases the other members instead of
    vanishing with the thread, the pool epilogue asserts that everyone
    wound down and nothing failed.
    """

    def __init__(self):
        self.errors = []
        self.refusals = 0
        self.stop = threading.Event()
        self._lock = threading.Lock()
        self._batches = []
        self._racers = []

    def spawn_batch(self, call, name):
        """Start a finite-loop member that leaves on its own."""
        return self._spawn(call, name, self._batches)

    def spawn_racer(self, call, name):
        """Start a member that loops until the stop releases it."""
        return self._spawn(call, name, self._racers)

    def _spawn(self, call, name, into):
        thread = threading.Thread(
            target=self._supervise, args=(call, name),
            name=name, daemon=True)
        thread.start()
        into.append(thread)
        return thread

    def _supervise(self, call, name):
        try:
            call()
        except BaseException:  # noqa: BLE001 - supervision collects even SystemExit
            with self._lock:
                self.errors.append((name, traceback.format_exc()))
            self.stop.set()

    def refuse(self):
        with self._lock:
            self.refusals += 1

    def join_batches(self, timeout=JOIN_TIMEOUT):
        # the racers keep running during this: only batch members are
        # joined, the stop event stays unset so the rider keeps working
        for thread in self._batches:
            thread.join(timeout=timeout)

    def stop_and_join(self, timeout=JOIN_TIMEOUT):
        self.stop.set()
        for thread in self._batches + self._racers:
            thread.join(timeout=timeout)
        alive = [
            t.name for t in self._batches + self._racers if t.is_alive()]
        assert not alive, f'hung storm threads: {alive[:10]!r}'
        assert not self.errors, f'storm calls failed: {self.errors[:3]!r}'


def _batch(check, iterations):
    def batch():
        for _ in range(iterations):
            check()
    return batch


def _gc_rider(storm):
    def rider():
        while not storm.stop.is_set():
            gc.collect()
            time.sleep(0.02)
    return rider


def _resizer(buf, storm):
    def resize():
        while not storm.stop.is_set():
            try:
                del buf[-1:]
                buf.extend(b'\x00')
            except BufferError:
                storm.refuse()
            time.sleep(0.001)
    return resize


def _output_decoder(storm, simplejpeg, jpeg, buf, reference):
    # BufferError around the acquisition would end up collected by the
    # pool: an output decoder can always win its own buffer back, a
    # refusal there is an anomaly like a wrong result
    def decode():
        while not storm.stop.is_set():
            result = simplejpeg.decode_jpeg(jpeg, buffer=buf)
            if not np.array_equal(result, reference):
                raise AssertionError(
                    'decoded bytes differ from the reference during '
                    'the resize race')
    return decode


def _input_decoder(storm, simplejpeg, buf):
    def decode():
        while not storm.stop.is_set():
            try:
                simplejpeg.decode_jpeg(buf)
            except ValueError:
                # a trim can slip in between two resizes: a shortened
                # bytearray is then a broken input, a documented user
                # error handled by ValueError
                pass
            except BufferError:
                storm.refuse()
    return decode


def _assert_fixtures_intact(fixtures):
    # the concurrent use must not mutate the shared fixtures
    assert np.array_equal(fixtures['image'], fixtures['image_snapshot'])
    assert bytes(fixtures['enc']['main']) == fixtures['jpeg_snapshot']


@pytest.fixture(scope='module')
def fixtures():
    image = generate_image(HEIGHT, WIDTH, 3)
    gray = generate_image(HEIGHT, WIDTH, 1)
    y = generate_image(HEIGHT, WIDTH, 1)[:, :, 0].copy()
    u = generate_image(HEIGHT // 2, WIDTH // 2, 1)[:, :, 0].copy()
    enc = {
        'main': simplejpeg.encode_jpeg(image, 98),
        'fast': simplejpeg.encode_jpeg(image, 98, fastdct=True),
        'gray': simplejpeg.encode_jpeg(
            gray, 98, colorspace='gray', colorsubsampling='gray'),
        'yuv': simplejpeg.encode_jpeg_yuv_planes(y, u, u.copy(), 98),
    }
    dec = {
        'rgb': simplejpeg.decode_jpeg(enc['main']),
        'gray': simplejpeg.decode_jpeg(enc['main'], colorspace='gray'),
        'fast': simplejpeg.decode_jpeg(enc['fast'], fastdct=True),
        'yuv': simplejpeg.decode_jpeg(enc['yuv']),
    }
    return {
        'simplejpeg': simplejpeg,
        'image': image,
        'gray': gray,
        'image_snapshot': image.copy(),
        'jpeg_snapshot': bytes(enc['main']),
        'planes': (y, u, u.copy()),
        'enc': enc,
        'dec': dec,
        'header': simplejpeg.decode_jpeg_header(enc['main']),
    }


@pytest.fixture(autouse=True)
def gil_off():
    # the marker only promises a free-threaded build: an import that
    # re-enables the GIL slips past the marker, the storm must not
    assert not sys._is_gil_enabled(), 'the GIL is enabled'


def _storm_groups(groups, fixtures):
    """
    Race the given check groups against each other under one wall budget.
    """
    threads = _thread_count()
    storm = _Storm()
    for name, check in groups:
        # warmup call: the first call carries one-time init cost
        check()
        start = time.perf_counter()
        check()
        duration = time.perf_counter() - start
        # the budget is the group's wall window: the iterations are
        # sized for the whole group, not per thread, so the wall stays
        # at BUDGET/cores no matter how many cores the leg has
        iters = max(4, min(int(BUDGET / max(duration, 1e-6) / threads), 5000))
        batch = _batch(check, iters)
        for index in range(threads):
            storm.spawn_batch(batch, f'{name}-{index}')
    storm.spawn_racer(_gc_rider(storm), 'gc')
    storm.join_batches()
    storm.stop_and_join()
    _assert_fixtures_intact(fixtures)


def _decode_check(fixtures, jpeg_key, reference_key, **options):
    """
    A check that decode_jpeg must reproduce the reference exactly.
    """
    simplejpeg = fixtures['simplejpeg']
    jpeg = fixtures['enc'][jpeg_key]
    reference = fixtures['dec'][reference_key]

    def check():
        if not np.array_equal(simplejpeg.decode_jpeg(jpeg, **options), reference):
            raise AssertionError('decoded bytes differ from the reference')
    return check


def _encode_check(fixtures, image_key, reference_key, **options):
    """
    A check that encode_jpeg must reproduce the reference exactly.
    """
    simplejpeg = fixtures['simplejpeg']
    image = fixtures[image_key]
    reference = fixtures['enc'][reference_key]

    def check():
        if simplejpeg.encode_jpeg(image, 98, **options) != reference:
            raise AssertionError('encoded bytes differ from the reference')
    return check


def _yuv_check(fixtures):
    """
    A check for both the color and the gray YUV plane encodings.
    """
    simplejpeg = fixtures['simplejpeg']
    y, u, v = fixtures['planes']
    yuv_reference = simplejpeg.encode_jpeg_yuv_planes(y, u, v, 98)
    gray_yuv_reference = simplejpeg.encode_jpeg_yuv_planes(y, None, None, 98)

    def check():
        if simplejpeg.encode_jpeg_yuv_planes(y, u, v, 98) != yuv_reference:
            raise AssertionError('yuv bytes differ from the reference')
        if simplejpeg.encode_jpeg_yuv_planes(
                y, None, None, 98) != gray_yuv_reference:
            raise AssertionError('gray yuv bytes differ from the reference')
    return check


def _header_check(fixtures):
    """
    A check that the decoded header must stay byte-stable.
    """
    def check():
        if fixtures['simplejpeg'].decode_jpeg_header(
                fixtures['enc']['main']) != fixtures['header']:
            raise AssertionError('header differs from the reference')
    return check


def _error_cases(fixtures):
    """
    Map one storm case per documented error path.
    """
    simplejpeg = fixtures['simplejpeg']
    enc = fixtures['enc']
    image = fixtures['image']
    y, u, v = fixtures['planes']
    garbage = bytes(bytearray(b'definitely not a jpeg'))
    truncated = bytes(enc['main'][:-32])
    too_small = bytearray(96)
    flipped = np.flipud(image)
    channels_wrong = np.resize(image, (HEIGHT, WIDTH, 2))
    oversized_u = np.resize(u, (HEIGHT, WIDTH))
    return {
        'decode garbage': (lambda: simplejpeg.decode_jpeg(garbage), 'JPEG'),
        # a trimmed file can fail with different libjpeg messages,
        # only the ValueError type assertion applies
        'decode truncated': (lambda: simplejpeg.decode_jpeg(truncated), None),
        'decode too small output': (
            lambda: simplejpeg.decode_jpeg(enc['main'], buffer=too_small),
            'too small',
        ),
        'encode wrong channels': (
            lambda: simplejpeg.encode_jpeg(channels_wrong, 98),
            'channels does not match',
        ),
        # the flipped view fails inside the compressor, its message
        # comes from libjpeg, not worth pinning
        'encode flipped rows': (
            lambda: simplejpeg.encode_jpeg(flipped, 98), None),
        'encode yuv missing V': (
            lambda: simplejpeg.encode_jpeg_yuv_planes(y, u, None, 98),
            'V (missing)',
        ),
        'encode yuv missing U': (
            lambda: simplejpeg.encode_jpeg_yuv_planes(y, None, v, 98),
            'U (missing)',
        ),
        'encode yuv shape mismatch': (
            lambda: simplejpeg.encode_jpeg_yuv_planes(y, oversized_u, v, 98),
            'U and V planes must have matching shape',
        ),
    }


def _error_check(function, message):
    """
    A check that the documented error path keeps raising what it raises
    today while the other storms race.
    """
    def check():
        try:
            function()
        except ValueError as e:
            if message is not None and message not in str(e):
                raise AssertionError(
                    f'unexpected error message: {str(e)!r}') from e
        except BaseException as e:
            raise AssertionError(
                f'unexpected {type(e)!r} raised: {str(e)!r}') from e
        else:
            expected = message if message is not None else 'ValueError'
            raise AssertionError(
                f'expected error {expected!r} was not raised')
    return check


_ERROR_CASE_NAMES = (
    'decode garbage', 'decode truncated', 'decode too small output',
    'encode wrong channels', 'encode flipped rows', 'encode yuv missing V',
    'encode yuv missing U', 'encode yuv shape mismatch',
)


@pytest.mark.free_threaded
@pytest.mark.parametrize('case_name', _ERROR_CASE_NAMES)
def test_error_path_keeps_raising_under_thread_races(fixtures, case_name):
    function, message = _error_cases(fixtures)[case_name]
    _storm_groups(
        [(f'error {case_name}', _error_check(function, message))], fixtures)


@pytest.mark.free_threaded
def test_decode_rgb_stays_byte_exact_under_thread_races(fixtures):
    _storm_groups([('decode rgb', _decode_check(fixtures, 'main', 'rgb'))], fixtures)


@pytest.mark.free_threaded
def test_decode_gray_stays_byte_exact_under_thread_races(fixtures):
    _storm_groups(
        [('decode gray', _decode_check(
            fixtures, 'main', 'gray', colorspace='gray'))], fixtures)


@pytest.mark.free_threaded
def test_decode_fastdct_stays_byte_exact_under_thread_races(fixtures):
    _storm_groups(
        [('decode fastdct', _decode_check(
            fixtures, 'fast', 'fast', fastdct=True))], fixtures)


@pytest.mark.free_threaded
def test_decode_yuv_stays_byte_exact_under_thread_races(fixtures):
    _storm_groups([('decode yuv', _decode_check(fixtures, 'yuv', 'yuv'))], fixtures)


@pytest.mark.free_threaded
def test_encode_rgb_stays_byte_exact_under_thread_races(fixtures):
    _storm_groups([('encode rgb', _encode_check(fixtures, 'image', 'main'))], fixtures)


@pytest.mark.free_threaded
def test_encode_fastdct_stays_byte_exact_under_thread_races(fixtures):
    _storm_groups(
        [('encode fastdct', _encode_check(
            fixtures, 'image', 'fast', fastdct=True))], fixtures)


@pytest.mark.free_threaded
def test_encode_gray_stays_byte_exact_under_thread_races(fixtures):
    _storm_groups(
        [('encode gray', _encode_check(
            fixtures, 'gray', 'gray',
            colorspace='gray', colorsubsampling='gray'))], fixtures)


@pytest.mark.free_threaded
def test_encode_yuv_stays_byte_exact_under_thread_races(fixtures):
    _storm_groups([('encode yuv', _yuv_check(fixtures))], fixtures)


@pytest.mark.free_threaded
def test_header_stays_byte_exact_under_thread_races(fixtures):
    _storm_groups([('header', _header_check(fixtures))], fixtures)


@pytest.mark.free_threaded
def test_decodes_survive_racing_output_buffer_resizes(fixtures):
    threads = _thread_count()
    simplejpeg = fixtures['simplejpeg']
    jpeg = fixtures['enc']['main']
    reference = fixtures['dec']['rgb']

    storm = _Storm()
    for index in range(max(2, threads // 2)):
        buf = bytearray(reference.nbytes)
        storm.spawn_racer(
            _output_decoder(storm, simplejpeg, jpeg, buf, reference),
            f'output-decode-{index}')
        storm.spawn_racer(_resizer(buf, storm), f'output-resize-{index}')
    storm.spawn_racer(_gc_rider(storm), 'gc')

    time.sleep(BUDGET)
    storm.stop_and_join()
    assert storm.refusals > 0, (
        f'no buffer-resize refusals observed with {threads} threads '
        '(expected refusals under contention)')
    _assert_fixtures_intact(fixtures)


@pytest.mark.free_threaded
def test_decodes_survive_racing_input_buffer_resizes(fixtures):
    threads = _thread_count()
    simplejpeg = fixtures['simplejpeg']
    jpeg = fixtures['enc']['main']

    storm = _Storm()
    for index in range(max(2, threads // 2)):
        buf = bytearray(jpeg)
        storm.spawn_racer(
            _input_decoder(storm, simplejpeg, buf), f'input-decode-{index}')
        storm.spawn_racer(_resizer(buf, storm), f'input-resize-{index}')
    storm.spawn_racer(_gc_rider(storm), 'gc')

    time.sleep(BUDGET)
    storm.stop_and_join()
    assert storm.refusals > 0, (
        f'no buffer-resize refusals observed with {threads} threads '
        '(expected refusals under contention)')
    _assert_fixtures_intact(fixtures)
