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

import numpy as np
from harness import generate_image
from rssize import page_size, rss

import simplejpeg


def _assert_no_growth(battery, warmup=256, count=1000):
    # first calls pay one-time allocations (jpeg tables, error buffers,
    # importer caches); afterwards a single long battery run must leave
    # the working set within the allowance. The working set only ever
    # moves in whole pages, so the allowance is expressed in page steps
    # and scales with the platform page size instead of assuming 4 KiB:
    # 64 KiB on 4 KiB pages, 256 KiB on 16 KiB Apple pages, 1 MiB on
    # 64 KiB pages. Linux and macOS runners measure flat at zero
    # growth; the windows-11-arm runners jitter between 4 and 8 page
    # steps per battery (first CI runs of 2026-11-20), so 16 pages
    # gives 2x the measured jitter while a leaked tjhandle adds one
    # page per call (~4 KiB of heap), around 1000 pages per battery
    battery(warmup)
    previous = rss()
    battery(count)
    growth = rss() - previous
    page = page_size()
    assert growth < 16 * page, (
        f'the working set grew by {growth} bytes '
        f'({growth // page} pages of {page} bytes) over {count} calls; '
        'one leaked tjhandle per call grows it by megabytes over the battery'
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
