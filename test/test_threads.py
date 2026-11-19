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

BUDGET = float(os.environ.get('STORM_BUDGET', 1.0))


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
    vanishing with the thread, the pool epilogue asserts assert that
    everyone wound down and nothing failed.
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
        except BaseException:
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
        assert not alive, 'hung storm threads: %r' % alive[:10]
        assert not self.errors, 'storm calls failed: %r' % (self.errors[:3],)


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


@pytest.mark.free_threaded
def test_pipeline_groups_stay_byte_exact_under_thread_races(fixtures):
    simplejpeg = fixtures['simplejpeg']
    enc, dec = fixtures['enc'], fixtures['dec']
    y, u, v = fixtures['planes']
    yuv_reference = simplejpeg.encode_jpeg_yuv_planes(y, u, v, 98)
    gray_yuv_reference = simplejpeg.encode_jpeg_yuv_planes(y, None, None, 98)

    garbage = bytes(bytearray(b'definitely not a jpeg'))
    truncated = bytes(enc['main'][:-32])
    too_small = bytearray(96)
    flipped = np.flipud(fixtures['image'])
    channels_wrong = np.resize(fixtures['image'], (HEIGHT, WIDTH, 2))
    oversized_u = np.resize(u, (HEIGHT, WIDTH))
    error_battery = [
        (lambda: simplejpeg.decode_jpeg(garbage), 'JPEG'),
        # a trimmed file can fail with different libjpeg messages,
        # only the ValueError type assertion applies
        (lambda: simplejpeg.decode_jpeg(truncated), None),
        (
            lambda: simplejpeg.decode_jpeg(enc['main'], buffer=too_small),
            'too small',
        ),
        (lambda: simplejpeg.encode_jpeg(channels_wrong, 98), 'channels does not match'),
        (lambda: simplejpeg.encode_jpeg(flipped, 98), None),
        (lambda: simplejpeg.encode_jpeg_yuv_planes(y, u, None, 98), 'V (missing)'),
        (lambda: simplejpeg.encode_jpeg_yuv_planes(y, None, v, 98), 'U (missing)'),
        (
            lambda: simplejpeg.encode_jpeg_yuv_planes(y, oversized_u, v, 98),
            'U and V planes must have matching shape',
        ),
    ]

    def error_check():
        for function, message in error_battery:
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
                    % (message if message is not None else 'ValueError',))

    def decode_check(jpeg, reference, **options):
        if not np.array_equal(simplejpeg.decode_jpeg(jpeg, **options), reference):
            raise AssertionError('decoded bytes differ from the reference')

    def encode_check(image, reference, **options):
        if simplejpeg.encode_jpeg(image, 98, **options) != reference:
            raise AssertionError('encoded bytes differ from the reference')

    def header_check():
        if simplejpeg.decode_jpeg_header(enc['main']) != fixtures['header']:
            raise AssertionError('header differs from the reference')

    def yuv_check():
        if simplejpeg.encode_jpeg_yuv_planes(y, u, v, 98) != yuv_reference:
            raise AssertionError('yuv bytes differ from the reference')
        if simplejpeg.encode_jpeg_yuv_planes(y, None, None, 98) != gray_yuv_reference:
            raise AssertionError('gray yuv bytes differ from the reference')

    groups = [
        ('decode rgb', lambda: decode_check(enc['main'], dec['rgb'])),
        ('decode gray', lambda: decode_check(
            enc['main'], dec['gray'], colorspace='gray')),
        ('decode fastdct', lambda: decode_check(
            enc['fast'], dec['fast'], fastdct=True)),
        ('decode yuv', lambda: decode_check(enc['yuv'], dec['yuv'])),
        ('encode rgb', lambda: encode_check(fixtures['image'], enc['main'])),
        ('encode fastdct', lambda: encode_check(
            fixtures['image'], enc['fast'], fastdct=True)),
        ('encode gray', lambda: encode_check(
            fixtures['gray'], enc['gray'],
            colorspace='gray', colorsubsampling='gray')),
        ('encode yuv', yuv_check),
        ('header', header_check),
        ('error paths', error_check),
    ]

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
            storm.spawn_batch(batch, '%s-%d' % (name, index))
    storm.spawn_racer(_gc_rider(storm), 'gc')

    # the batches wind down on their own while the rider keeps working,
    # then the stop releases the rider for the epilogue
    storm.join_batches()
    storm.stop_and_join()
    _assert_fixtures_intact(fixtures)


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
            'output-decode-%d' % index)
        storm.spawn_racer(_resizer(buf, storm), 'output-resize-%d' % index)
    storm.spawn_racer(_gc_rider(storm), 'gc')

    time.sleep(BUDGET)
    storm.stop_and_join()
    assert storm.refusals > 0, (
        'no buffer-resize refusals observed with %d threads '
        '(expected refusals under contention)' % threads)
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
            _input_decoder(storm, simplejpeg, buf), 'input-decode-%d' % index)
        storm.spawn_racer(_resizer(buf, storm), 'input-resize-%d' % index)
    storm.spawn_racer(_gc_rider(storm), 'gc')

    time.sleep(BUDGET)
    storm.stop_and_join()
    assert storm.refusals > 0, (
        'no buffer-resize refusals observed with %d threads '
        '(expected refusals under contention)' % threads)
    _assert_fixtures_intact(fixtures)
