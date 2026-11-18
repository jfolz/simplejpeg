"""
Resource leak tests: every call must release its native resources.

tjhandles exist only as C allocations, invisible to Python refcounting,
so the tests work at the RSS level: a call that leaks its handle grows
the process working set batch by batch, while a clean call reuses the
same working set. The error-path battery runs the raising calls too,
since that is where the try/finally resource release has to work
hardest.
"""

import contextlib
import ctypes
import sys

import numpy as np
import pytest
from harness import generate_image

import simplejpeg


def _rss_bytes():
    """Working set of the current process, None when not measurable."""
    if sys.platform == 'win32':
        class MEMORY_COUNTERS(ctypes.Structure):
            _fields_ = [
                ('cb', ctypes.c_uint32),
                ('page_faults', ctypes.c_uint32),
                ('peak_working_set', ctypes.c_size_t),
                ('working_set', ctypes.c_size_t),
                ('quota_peak_paged_pool', ctypes.c_size_t),
                ('quota_paged_pool', ctypes.c_size_t),
                ('quota_peak_non_paged_pool', ctypes.c_size_t),
                ('quota_non_paged_pool', ctypes.c_size_t),
                ('pagefile', ctypes.c_size_t),
                ('peak_pagefile', ctypes.c_size_t),
            ]

        counters = MEMORY_COUNTERS()
        counters.cb = ctypes.sizeof(counters)
        process = ctypes.windll.kernel32.GetCurrentProcess()
        if not ctypes.windll.psapi.GetProcessMemoryInfo(
                process, ctypes.byref(counters), counters.cb):
            return None
        return counters.working_set
    import resource
    maxrss = resource.getrusage(resource.RUSAGE_SELF).ru_maxrss
    if sys.platform == 'darwin':
        return maxrss
    return maxrss * 1024


@pytest.fixture(name='rss')
def fixture_rss():
    if _rss_bytes() is None:
        pytest.skip('no working set measurement available')
    return _rss_bytes


def _assert_batches(rss, battery, warmup=256, batch=2000):
    # first calls pay one-time allocations (jpeg tables, error buffers,
    # importer caches), the following batches must plateau: some working
    # set drift by other causes (allocator arena moves, caches, working
    # set jitter) is expected and allowed, but if an operation leaks, it
    # leaks every call: a leaking batch then grows by one page per call,
    # 2000 pages (~8 MiB) per batch, while the allowance of 64 KiB is a
    # fraction of that on both GIL and free-threaded builds. the growth
    # is instead treated as the operation holding references, which the
    # refcount check on the inputs catches
    battery(warmup)
    previous = rss()
    for _ in range(3):
        battery(batch)
        current = rss()
        assert current - previous < 64 * 1024, (
            f'the working set grew by {current - previous} bytes during '
            f'a batch of {batch} calls, background drift is a few KiB '
            f'while a leaked tjhandle costs 4096 bytes per call'
        )
        previous = current


def test_decode_releases_tjhandles(rss):
    data = simplejpeg.encode_jpeg(generate_image(33, 47, 3), 98)

    def battery(count):
        for _ in range(count):
            simplejpeg.decode_jpeg(data)

    _assert_batches(rss, battery)


def test_decode_with_buffer_releases_tjhandles(rss):
    data = simplejpeg.encode_jpeg(generate_image(33, 47, 3), 98)
    height, width, _, _ = simplejpeg.decode_jpeg_header(data)
    buffer = bytearray(height * width * 3)

    def battery(count):
        for _ in range(count):
            simplejpeg.decode_jpeg(data, buffer=buffer)

    _assert_batches(rss, battery)


def test_decode_header_releases_tjhandles(rss):
    data = simplejpeg.encode_jpeg(generate_image(33, 47, 3), 98)

    def battery(count):
        for _ in range(count):
            simplejpeg.decode_jpeg_header(data)

    _assert_batches(rss, battery)


def test_encode_releases_tjhandles(rss):
    im = generate_image(33, 47, 3)

    def battery(count):
        for _ in range(count):
            simplejpeg.encode_jpeg(im, 98)

    _assert_batches(rss, battery)


def test_encode_yuv_releases_tjhandles(rss):
    # even dimensions: turbojpeg walks padded plane rows, odd widths give
    # strides below the padding and raise inside the compressor
    im = generate_image(32, 48, 3)
    y = im[:, :, 0].copy()
    u = im[:16, :24, 0].copy()
    v = im[:16, :24, 2].copy()

    def battery(count):
        for _ in range(count):
            simplejpeg.encode_jpeg_yuv_planes(y, u, v, 98)
            simplejpeg.encode_jpeg_yuv_planes(y, None, None, 98)

    _assert_batches(rss, battery)


def test_error_paths_release_tjhandles(rss):
    im = generate_image(33, 47, 3)
    data = simplejpeg.encode_jpeg(im, 98)
    garbage = bytes(bytearray(b'definitely not a jpeg'))
    truncated = data[:-8]
    strided = np.zeros((3, 33, 47), dtype=np.uint8).transpose((1, 2, 0))
    channels = np.resize(im, (33, 47, 2))

    def battery(count):
        # every iteration raises on one of the documented error paths:
        # the decoder and encoder handles created for each call must be
        # destroyed on the way out regardless
        for _ in range(count):
            with contextlib.suppress(ValueError):
                simplejpeg.decode_jpeg(garbage)
            with contextlib.suppress(ValueError):
                simplejpeg.decode_jpeg(truncated)
            with contextlib.suppress(ValueError):
                simplejpeg.decode_jpeg(data, buffer=bytearray(12))
            with contextlib.suppress(ValueError):
                simplejpeg.encode_jpeg(channels, 98)
            with contextlib.suppress(ValueError):
                simplejpeg.encode_jpeg(strided, 98)

    _assert_batches(rss, battery)
