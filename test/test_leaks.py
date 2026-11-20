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
import os
import warnings

import numpy as np
import pytest
from harness import generate_image
from rssize import rss

import simplejpeg

pytestmark = pytest.mark.skipif(
    'sanitize' in (os.environ.get('CFLAGS', '') + os.environ.get('LDFLAGS', '')),
    reason='working set batteries are meaningless under sanitizer builds '
           '(quarantine and redzones inflate the working set); real leaks '
           'are still caught by LeakSanitizer at process exit')


def _assert_no_growth(battery, warmup=256, count=1000, bytes_per_iteration=400):
    # Assert that RSS does not grow for test battery.
    # Warmup first to account for one-time allocations,
    # followed by the longer test run.
    # There may be minor jitter and memory fragmentation between readings,
    # accounted for by an allowance given as bytes per iteration.
    battery(warmup)
    previous = rss()
    battery(count)
    growth = rss() - previous
    allowance = bytes_per_iteration * count
    if growth > allowance // 2:
        warnings.warn(f'RSS grew by {growth} bytes, {growth / allowance:.0%} of the allowance')
    assert growth <= allowance, (
        f'RSS grew {growth / count:.1f} per iteration, exceeding allowed {bytes_per_iteration} bytes'
    )


def test_decode_tjhandle_released():
    data = simplejpeg.encode_jpeg(generate_image(33, 47, 3), 98)

    def battery(count):
        for _ in range(count):
            simplejpeg.decode_jpeg(data)

    _assert_no_growth(battery)


def test_decode_tjhandle_released_with_buffer():
    data = simplejpeg.encode_jpeg(generate_image(33, 47, 3), 98)
    height, width, _, _ = simplejpeg.decode_jpeg_header(data)
    buffer = bytearray(height * width * 3)

    def battery(count):
        for _ in range(count):
            simplejpeg.decode_jpeg(data, buffer=buffer)

    _assert_no_growth(battery)


def test_decode_header_tjhandle_released():
    data = simplejpeg.encode_jpeg(generate_image(33, 47, 3), 98)

    def battery(count):
        for _ in range(count):
            simplejpeg.decode_jpeg_header(data)

    _assert_no_growth(battery)


def test_encode_tjhandle_released():
    im = generate_image(33, 47, 3)

    def battery(count):
        for _ in range(count):
            simplejpeg.encode_jpeg(im, 98)

    _assert_no_growth(battery)


def test_encode_yuv_tjhandle_released():
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

    _assert_no_growth(battery)


def test_decode_tjhandle_released_garbage():
    garbage = bytes(bytearray(b'definitely not a jpeg'))

    def battery(count):
        for _ in range(count):
            with contextlib.suppress(ValueError):
                simplejpeg.decode_jpeg(garbage)

    _assert_no_growth(battery)


def test_decode_tjhandle_released_truncated():
    data = simplejpeg.encode_jpeg(generate_image(33, 47, 3), 98)
    truncated = data[:-8]

    def battery(count):
        for _ in range(count):
            with contextlib.suppress(ValueError):
                simplejpeg.decode_jpeg(truncated)

    _assert_no_growth(battery)


def test_decode_tjhandle_released_too_small_buffer():
    data = simplejpeg.encode_jpeg(generate_image(33, 47, 3), 98)

    def battery(count):
        for _ in range(count):
            with contextlib.suppress(ValueError):
                simplejpeg.decode_jpeg(data, buffer=bytearray(12))

    _assert_no_growth(battery)


def test_encode_tjhandle_released_channels():
    im = generate_image(33, 47, 3)
    channels = np.resize(im, (33, 47, 2))

    def battery(count):
        for _ in range(count):
            with contextlib.suppress(ValueError):
                simplejpeg.encode_jpeg(channels, 98)

    _assert_no_growth(battery)


def test_encode_tjhandle_released_strided():
    strided = np.zeros((3, 33, 47), dtype=np.uint8).transpose((1, 2, 0))

    def battery(count):
        for _ in range(count):
            with contextlib.suppress(ValueError):
                simplejpeg.encode_jpeg(strided, 98)

    _assert_no_growth(battery)
