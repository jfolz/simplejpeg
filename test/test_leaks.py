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


def _assert_no_growth(battery, warmup=256, count=1000, leak_bytes=400):
    # warmup first: the first calls pay one-time allocations (jpeg
    # tables, error buffers, importer caches). the allowance is per
    # battery iteration in bytes: a leaked tjhandle costs around
    # 4.1 KiB per call, 400 bytes per call is a 10th of that, while
    # working set jitter from the runners stayed below half of it in
    # CI (worst observed: ~200 bytes per call on windows arm64).
    # growing past half the allowance warns, so the bound can be
    # retuned before it fails a run
    battery(warmup)
    previous = rss()
    battery(count)
    growth = rss() - previous
    allowance = leak_bytes * count
    if growth > allowance // 2:
        warnings.warn(
            f'the leak battery measured {growth} bytes of working set '
            f'growth, {growth / allowance:.0%} of the {allowance} byte '
            'allowance: consider retuning the leak test bounds')
    assert growth <= allowance, (
        f'the working set grew by {growth} bytes over {count} calls, '
        f'around {growth // count} bytes per call; '
        f'the allowance is {leak_bytes} bytes per call, a 10th of a '
        'leaked tjhandle (~4.1 KiB)'
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


def test_error_paths_release_tjhandles():
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

    _assert_no_growth(battery)
