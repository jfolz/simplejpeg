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
import warnings

import numpy as np
from harness import generate_image
from rssize import rss

import simplejpeg


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


def test_decode_releases_tjhandles():
    data = simplejpeg.encode_jpeg(generate_image(33, 47, 3), 98)

    def battery(count):
        for _ in range(count):
            simplejpeg.decode_jpeg(data)

    _assert_no_growth(battery)


def test_decode_with_buffer_releases_tjhandles():
    data = simplejpeg.encode_jpeg(generate_image(33, 47, 3), 98)
    height, width, _, _ = simplejpeg.decode_jpeg_header(data)
    buffer = bytearray(height * width * 3)

    def battery(count):
        for _ in range(count):
            simplejpeg.decode_jpeg(data, buffer=buffer)

    _assert_no_growth(battery)


def test_decode_header_releases_tjhandles():
    data = simplejpeg.encode_jpeg(generate_image(33, 47, 3), 98)

    def battery(count):
        for _ in range(count):
            simplejpeg.decode_jpeg_header(data)

    _assert_no_growth(battery)


def test_encode_releases_tjhandles():
    im = generate_image(33, 47, 3)

    def battery(count):
        for _ in range(count):
            simplejpeg.encode_jpeg(im, 98)

    _assert_no_growth(battery)


def test_encode_yuv_releases_tjhandles():
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


def test_decode_garbage_releases_tjhandles():
    garbage = bytes(bytearray(b'definitely not a jpeg'))

    def battery(count):
        for _ in range(count):
            with contextlib.suppress(ValueError):
                simplejpeg.decode_jpeg(garbage)

    _assert_no_growth(battery)


def test_decode_truncated_releases_tjhandles():
    data = simplejpeg.encode_jpeg(generate_image(33, 47, 3), 98)
    truncated = data[:-8]

    def battery(count):
        for _ in range(count):
            with contextlib.suppress(ValueError):
                simplejpeg.decode_jpeg(truncated)

    _assert_no_growth(battery)


def test_decode_too_small_buffer_releases_tjhandles():
    data = simplejpeg.encode_jpeg(generate_image(33, 47, 3), 98)

    def battery(count):
        for _ in range(count):
            with contextlib.suppress(ValueError):
                simplejpeg.decode_jpeg(data, buffer=bytearray(12))

    _assert_no_growth(battery)


def test_encode_channels_releases_tjhandles():
    im = generate_image(33, 47, 3)
    channels = np.resize(im, (33, 47, 2))

    def battery(count):
        for _ in range(count):
            with contextlib.suppress(ValueError):
                simplejpeg.encode_jpeg(channels, 98)

    _assert_no_growth(battery)


def test_encode_strided_releases_tjhandles():
    strided = np.zeros((3, 33, 47), dtype=np.uint8).transpose((1, 2, 0))

    def battery(count):
        for _ in range(count):
            with contextlib.suppress(ValueError):
                simplejpeg.encode_jpeg(strided, 98)

    _assert_no_growth(battery)
