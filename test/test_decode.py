import os.path as pt
import threading
import time
from array import array

import numpy as np
import pytest
from harness import (
    assert_released_after_call,
    assert_released_after_error,
    mean_absolute_difference,
)

import simplejpeg

ROOT = pt.abspath(pt.dirname(__file__))


def delta_decode(array):
    # reconstruct pixel values from a row-delta encoded reference array
    return np.cumsum(array, axis=0, dtype=np.uint8)


def yield_reference_images():
    # reference pixel data produced by generate_references.py
    with np.load(pt.join(ROOT, 'reference_data.npz')) as archive:
        for name in archive.files:
            with open(pt.join(ROOT, 'images', name + '.jpg'), 'rb') as fp:
                data = fp.read()
            yield name, data, delta_decode(archive[name])


def test_header():
    for f, data, ref in yield_reference_images():
        height, width, _, _ = simplejpeg.decode_jpeg_header(data)
        assert width == ref.shape[1] and height == ref.shape[0], f


def test_rgb():
    for f, data, ref in yield_reference_images():
        sim = simplejpeg.decode_jpeg(data)
        assert mean_absolute_difference(ref, sim) < 1, f


def rgb2gray(rgb):
    # fixpoint version of rgb to gray conversion
    return (19595 * rgb[..., 0].astype(np.int32) +
            38470 * rgb[..., 1].astype(np.int32) +
            7471 * rgb[..., 2].astype(np.int32) + 32768) >> 16


def test_gray():
    for f, data, ref in yield_reference_images():
        expected = rgb2gray(ref)
        _, _, colorspace, _ = simplejpeg.decode_jpeg_header(data)
        # skip here because of high error bound,
        # test separately in test_decode_cmyk_gray
        if colorspace == 'CMYK':
            continue
        sim = simplejpeg.decode_jpeg(data, 'gray')
        assert mean_absolute_difference(expected, sim[..., 0]) < 1, f


def test_buffer():
    # large enough for the largest reference image (height * width * 3)
    b = bytearray(1024*1024*3)
    for f, data, ref in yield_reference_images():
        sim = simplejpeg.decode_jpeg(data, buffer=b)
        assert mean_absolute_difference(ref, sim) < 1, f


def test_buffer_insufficient():
    for _, data, ref in yield_reference_images():
        b = bytearray(ref.size - 1)
        with pytest.raises(ValueError, match='too small'):
            simplejpeg.decode_jpeg(data, buffer=b)


def test_truncated():
    for _, data, _ in yield_reference_images():
        with pytest.raises(ValueError, match='Premature end of JPEG file'):
            simplejpeg.decode_jpeg(data[:-1])


def test_fastdct():
    for f, data, ref in yield_reference_images():
        sim = simplejpeg.decode_jpeg(data, fastdct=True)
        assert mean_absolute_difference(ref, sim) < 2, f


def test_fastupsample():
    for f, data, ref in yield_reference_images():
        sim = simplejpeg.decode_jpeg(data, fastupsample=True)
        assert mean_absolute_difference(ref, sim) < 2, f


def test_fastdct_fastupsample():
    for f, data, ref in yield_reference_images():
        sim = simplejpeg.decode_jpeg(data, fastdct=True, fastupsample=True)
        assert mean_absolute_difference(ref, sim) < 3, f


def test_min_width_height():
    for f, data, ref in yield_reference_images():
        h, w = ref.shape[:2]
        # half height, but require original width
        sim = simplejpeg.decode_jpeg(data, min_height=h/2, min_width=w)
        assert sim.shape[0] == h, f
        # half width, but require original height
        sim = simplejpeg.decode_jpeg(data, min_width=w/2, min_height=h)
        assert sim.shape[1] == w, f
        # half height
        sim = simplejpeg.decode_jpeg(data, min_height=h/2)
        assert h/2 <= sim.shape[0] < h, f
        # half height, but require minimum factor greater 2
        sim = simplejpeg.decode_jpeg(data, min_height=h/2, min_factor=2.01)
        assert sim.shape[0] == h, f
        # half width
        sim = simplejpeg.decode_jpeg(data, min_width=w/2, min_height=1)
        assert w/2 <= sim.shape[1] < w, f
        # half width, but require minimum factor greater 2
        sim = simplejpeg.decode_jpeg(data, min_width=w/2, min_height=1, min_factor=2.01)
        assert sim.shape[1] == w, f


def _colorspace_to_rgb(sim, colorspace):
    ind = colorspace.index('R'), colorspace.index('G'), colorspace.index('B')
    out = np.zeros(sim.shape[:2] + (3,))
    out[...] = sim[:, :, ind]
    return out


def test_colorspace():
    for f, data, ref in yield_reference_images():
        for colorspace in ('RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR',
                           'XRGB', 'RGBA', 'BGRA', 'ABGR', 'ARGB'):
            sim = simplejpeg.decode_jpeg(data, colorspace)
            sim = _colorspace_to_rgb(sim, colorspace)
            assert mean_absolute_difference(ref, sim) < 1, f


def test_writable():
    # bytes objects are read-only and reject a writable buffer request
    b = b'x' * 16
    for _, data, _ in yield_reference_images():
        with pytest.raises((BufferError, ValueError), match='writable'):
            simplejpeg.decode_jpeg(data, buffer=b)


def test_resize_buffer_concurrent():
    # create a big jpeg that takes a while to decode
    image = np.random.default_rng(1337).integers(
        0, 255, size=(2048, 2048, 3), dtype=np.uint8,
    )
    data = simplejpeg.encode_jpeg(image)
    height, width, _, _ = simplejpeg.decode_jpeg_header(data)
    size = height * width * 3  # default 'rgb' colorspace

    # function to decode in another thread and receive results
    decode_error = None
    decoded_image = None
    def decode():
        nonlocal decode_error, decoded_image
        try:
            decoded_image = simplejpeg.decode_jpeg(data, buffer=buf)
        except Exception as e:  # noqa: BLE001
            decode_error = e

    # measure how long decoding takes
    decode_durations = []
    for _ in range(3):
        start = time.monotonic()
        simplejpeg.decode_jpeg(data)
        decode_durations.append(time.monotonic() - start)
    decode_duration = max(decode_durations)

    # create an output buffer that is 1 bigger than we need
    # so we can safely chop it off later
    buf = bytearray(size + 1)
    decode_thread = threading.Thread(target=decode)
    decode_thread.start()

    # provoke a buffer error by resizing the bytearray while it's exported
    # use decode duration to schedule trials
    with pytest.raises(BufferError):
        time.sleep(0.05 * decode_duration)
        for _ in range(11):
            del buf[-1:]
            buf += b'\x00'
            time.sleep(0.1 * decode_duration)

    # verify that the image still decoded correctly
    decode_thread.join()
    if decode_error is not None:
        raise decode_error
    assert decoded_image is not None
    assert decoded_image.shape == (height, width, 3)


def _rgb_jpeg():
    rng = np.random.default_rng(1337)
    return simplejpeg.encode_jpeg(
        rng.integers(0, 255, size=(64, 64, 3), dtype=np.uint8))


def test_buffers_released_rgb():
    # input and output buffers stay exported only for the duration of
    # the call: resizing after the call must stay clean, a BufferError
    # would mean a leaked export
    data = bytearray(_rgb_jpeg())
    buffer = bytearray(64 * 64 * 3)

    def decode(data, buffer):
        return simplejpeg.decode_jpeg(data, buffer=buffer)

    assert_released_after_call(decode, data, buffer)


def test_buffers_released_yuv():
    rng = np.random.default_rng(1337)
    data = bytearray(simplejpeg.encode_jpeg_yuv_planes(
        rng.integers(0, 255, size=(64, 64), dtype=np.uint8),
        rng.integers(0, 255, size=(32, 32), dtype=np.uint8),
        rng.integers(0, 255, size=(32, 32), dtype=np.uint8)))
    buffer = bytearray(64 * 64 * 3)

    def decode(data, buffer):
        return simplejpeg.decode_jpeg(data, buffer=buffer)

    assert_released_after_call(decode, data, buffer)


def test_buffers_released_garbage():
    garbage = bytearray(b'definitely not a jpeg')
    buffer = bytearray(64 * 64 * 3)

    def decode(data, buffer):
        return simplejpeg.decode_jpeg(data, buffer=buffer)

    assert_released_after_error(decode, garbage, buffer, match='JPEG')


def test_buffers_released_truncated():
    # the truncated failure happens mid-decode, with a decoder and both
    # buffers exported along the way
    data = bytearray(_rgb_jpeg()[:-8])
    buffer = bytearray(64 * 64 * 3)

    def decode(data, buffer):
        return simplejpeg.decode_jpeg(data, buffer=buffer)

    assert_released_after_error(decode, data, buffer, match='Premature end of JPEG file')


def test_buffers_released_too_small():
    data = bytearray(_rgb_jpeg())
    buffer = bytearray(64 * 64 * 3 - 1)

    def decode(data, buffer):
        return simplejpeg.decode_jpeg(data, buffer=buffer)

    assert_released_after_error(decode, data, buffer, match='too small')


def test_header_buffers_released_garbage():
    # the header does the same input buffer handling without output
    garbage = bytearray(b'definitely not a jpeg')

    def decode_header(data):
        return simplejpeg.decode_jpeg_header(data)

    assert_released_after_error(decode_header, garbage, match='JPEG')


def test_header_buffers_released():
    # the outputs are ints and module-cached strings, they have no
    # refcount that could increase: only the release of the input is
    # observable and verified here
    data = bytearray(_rgb_jpeg())

    def decode_header(data):
        return simplejpeg.decode_jpeg_header(data)

    assert_released_after_call(decode_header, data)


def test_buffers_released_readonly():
    # a read-only buffer must be refused to decode into and release its
    # export on the way out
    data = bytearray(_rgb_jpeg())
    buffer = bytes(64 * 64 * 3)

    def decode(data, buffer):
        return simplejpeg.decode_jpeg(data, buffer=buffer)

    assert_released_after_error(decode, data, buffer, error=(BufferError, ValueError), match='writable')


def test_buffers_released_strided():
    # a 3-D array with row strides that are not contiguous cannot be
    # written into, the transpose gives it the right shape for that
    data = bytearray(_rgb_jpeg())
    buffer = np.zeros((3, 1024, 1024), dtype=np.uint8).transpose((1, 2, 0))

    def decode(data, buffer):
        return simplejpeg.decode_jpeg(data, buffer=buffer)

    assert_released_after_error(decode, data, buffer, match='contiguous')


def test_buffers_released_array_input():
    # array.array has the same export-refusing resize semantics as
    # bytearray and must release its export after the call as well
    data = array('B', _rgb_jpeg())
    buffer = bytearray(64 * 64 * 3)

    def decode(data, buffer):
        return simplejpeg.decode_jpeg(data, buffer=buffer)

    assert_released_after_call(decode, data, buffer)


def test_noncontiguous():
    b = np.zeros((3, 1024, 1024), dtype=np.uint8)
    for _, data, _ in yield_reference_images():
        with pytest.raises(ValueError, match='contiguous'):
            simplejpeg.decode_jpeg(data, buffer=b.transpose((1, 2, 0)))


def test_cmyk():
    for name in ('peppers_cmyk', 'cat_cmyk'):
        with open(pt.join(ROOT, 'images', name + '.jpg'), 'rb') as fp:
            data = fp.read()
        height, width, colorspace, subsampling = simplejpeg.decode_jpeg_header(data)
        assert colorspace == 'CMYK' and subsampling == '444', name
        cmyk = simplejpeg.decode_jpeg(data, 'cmyk')
        assert cmyk.shape == (height, width, 4)
        rgba = simplejpeg.decode_jpeg(data, 'RGBA')
        rgb = simplejpeg.decode_jpeg(data, 'rgb')
        np.testing.assert_array_equal(rgba[..., :3], rgb, name)


def _cmyk_reference(cmyk, colorspace):
    out = np.empty(cmyk.shape[:2] + (4,), dtype=np.uint8)
    k = cmyk[..., 3].astype(np.int32)
    r_off, g_off, b_off, a_off = {
        'RGBA': (0, 1, 2, 3),
        'BGRA': (2, 1, 0, 3),
        'ABGR': (3, 2, 1, 0),
        'ARGB': (1, 2, 3, 0),
    }[colorspace]
    for src, dst in zip(range(3), (r_off, g_off, b_off)):
        c = cmyk[..., src].astype(np.int32)
        out[..., dst] = (k - ((255 - c) * k >> 8)).astype(np.uint8)
    out[..., a_off] = 255
    return out


def test_cmyk_alpha():
    for name in ('peppers_cmyk', 'cat_cmyk'):
        with open(pt.join(ROOT, 'images', name + '.jpg'), 'rb') as fp:
            data = fp.read()
        cmyk = simplejpeg.decode_jpeg(data, 'cmyk')
        for colorspace in ('RGBA', 'BGRA', 'ABGR', 'ARGB'):
            sim = simplejpeg.decode_jpeg(data, colorspace)
            np.testing.assert_array_equal(
                sim, _cmyk_reference(cmyk, colorspace), name
            )


def cmyk2gray(cmyk):
    k = cmyk[..., 3].astype(np.int32)
    channels = [
        k - ((255 - cmyk[..., i].astype(np.int32)) * k >> 8)
        for i in range(3)
    ]
    return ((4899 * channels[0] + 9617 * channels[1]
        + 1868 * channels[2] + 8192) >> 14).astype(np.uint8)


def test_cmyk_gray():
    for name in ('peppers_cmyk', 'cat_cmyk'):
        with open(pt.join(ROOT, 'images', name + '.jpg'), 'rb') as fp:
            data = fp.read()
        cmyk = simplejpeg.decode_jpeg(data, 'cmyk')
        sim = simplejpeg.decode_jpeg(data, 'gray')
        gray = cmyk2gray(cmyk)
        np.testing.assert_array_equal(sim[..., 0], gray, name)


def test_cmyk_rgb():
    for f, data, ref in yield_reference_images():
        if not f.endswith('_cmyk'):
            continue
        sim = simplejpeg.decode_jpeg(data, 'rgb')
        assert mean_absolute_difference(ref, sim) < 2, f
