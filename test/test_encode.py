import os.path as pt

import numpy as np
import pytest
from numpy.lib.stride_tricks import sliding_window_view

import simplejpeg

ROOT = pt.abspath(pt.dirname(__file__))


def mean_absolute_difference(a, b):
    return np.abs(a.astype(np.float32) - b.astype(np.float32)).mean()


def _box_blur(image, radius):
    # soften the block edges of the synthetic image so that encoding with
    # chroma subsampling behaves like on natural images
    padded = np.pad(image, [(radius, radius), (radius, radius), (0, 0)],
                    mode='edge').astype(np.float32)
    return sliding_window_view(padded, (2*radius + 1, 2*radius + 1),
                               axis=(0, 1)).mean(axis=(-1, -2))


def generate_image(height=800, width=600, channels=3):
    rng = np.random.default_rng(9)
    # blocks of constant color reduce the amount of high frequency noise,
    # which makes encoding with chroma subsampling less lossy
    arr = rng.integers(
        0, 255, (max(1, -(-height // 8)), max(1, -(-width // 8)), channels),
        dtype=np.uint8,
    )
    arr = arr.repeat(8, axis=0)[:height].repeat(8, axis=1)[:, :width]
    arr = _box_blur(arr, 6)
    return np.ascontiguousarray(np.rint(arr).astype(np.uint8))


def test_encode_decode():
    im = generate_image(1689, 1000)
    encoded = simplejpeg.encode_jpeg(im, 98)
    decoded = simplejpeg.decode_jpeg(encoded)
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_encode_decode_subsampling():
    im = generate_image(679, 657)
    for subsampling, delta in (('422', 2), ('420', 3), ('440', 3), ('411', 9)):
        encoded = simplejpeg.encode_jpeg(im, 98, colorsubsampling=subsampling)
        decoded = simplejpeg.decode_jpeg(encoded)
        assert 0 < mean_absolute_difference(im, decoded) < delta, subsampling


def test_encode_fastdct():
    im = generate_image(345, 5448)
    encoded_fast = simplejpeg.encode_jpeg(im, 98, fastdct=True)
    decoded_fast = simplejpeg.decode_jpeg(encoded_fast)
    assert 0 < mean_absolute_difference(im, decoded_fast) < 2


def test_encode_grayscale():
    im = generate_image(589, 486, 1)
    encoded = simplejpeg.encode_jpeg(im, 98, colorspace='gray')
    decoded = simplejpeg.decode_jpeg(encoded, 'gray')
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_encode_grayscale_newaxis():
    im = generate_image(589, 486, 1)
    # make array 2D
    im = im[:, :, 0]
    # add back a channel axis with newaxis
    im = im[:, :, np.newaxis]
    encoded = simplejpeg.encode_jpeg(im, 98, colorspace='gray')
    decoded = simplejpeg.decode_jpeg(encoded, 'gray')
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_encode_colorspace():
    im = generate_image(589, 486, 4)
    for colorspace in ('RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR',
                       'XRGB', 'RGBA', 'BGRA', 'ABGR', 'ARGB'):
        np_im = np.ascontiguousarray(im[:, :, :len(colorspace)])
        encoded = simplejpeg.encode_jpeg(np_im, 98, colorspace=colorspace)
        decoded = simplejpeg.decode_jpeg(encoded, colorspace)
        ind = colorspace.index('R'), colorspace.index('G'), colorspace.index('B')
        assert 0 < mean_absolute_difference(np_im[..., ind], decoded[..., ind]) < 2, colorspace
        if 'A' in colorspace:
            assert np.all(decoded[..., colorspace.index('A')] == 255), colorspace


def test_encode_noncontiguous():
    im = np.zeros((3, 123, 235), dtype=np.uint8)
    with pytest.raises(ValueError, match='contiguous rows'):
        simplejpeg.encode_jpeg(im.transpose((1, 2, 0)))


def test_encode_decode_padding_start():
    im = generate_image(600, 1000)
    # make an image that has padding bytes at the start of each row
    im = im[:, 200:, :]
    encoded = simplejpeg.encode_jpeg(im, 98)
    decoded = simplejpeg.decode_jpeg(encoded)
    assert decoded.shape == (600, 800, 3)
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_encode_decode_padding_end():
    im = generate_image(600, 1000)
    # make an image that has padding bytes at the end of each row
    im = im[:, :800, :]
    encoded = simplejpeg.encode_jpeg(im, 98)
    decoded = simplejpeg.decode_jpeg(encoded)
    assert decoded.shape == (600, 800, 3)
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_encode_decode_padding_both():
    im = generate_image(600, 1000)
    # make an image that has padding bytes at the start and end of each row
    im = im[:, 100:900, :]
    encoded = simplejpeg.encode_jpeg(im, 98)
    decoded = simplejpeg.decode_jpeg(encoded)
    assert decoded.shape == (600, 800, 3)
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_encode_2d():
    im = np.zeros((589, 486), dtype=np.uint8)
    with pytest.raises(ValueError, match='wrong number of dimensions'):
        simplejpeg.encode_jpeg(im, 98, colorspace='gray')


def test_encode_broadcast_row():
    width, height, channels = 593, 132, 3
    im = np.zeros((width, channels), dtype=np.uint8)
    im = im[np.newaxis, :, :]
    im = np.broadcast_to(im, (height, width, channels))
    with pytest.raises(ValueError, match='broadcasting rows is not supported'):
        simplejpeg.encode_jpeg(im, 98, colorspace='rgb')


def test_encode_cmyk():
    with open(pt.join(ROOT, 'images', 'peppers_cmyk.jpg'), 'rb') as fp:
        data = fp.read()
    cmyk_input = simplejpeg.decode_jpeg(data, 'cmyk')
    encoded = simplejpeg.encode_jpeg(cmyk_input, 95, colorspace='cmyk')
    height, width, colorspace, subsampling = simplejpeg.decode_jpeg_header(encoded)
    assert (height, width) == cmyk_input.shape[:2]
    assert colorspace == 'YCCK' and subsampling == '444', (colorspace, subsampling)
    decoded = simplejpeg.decode_jpeg(encoded, 'CMYK')
    assert decoded.shape == cmyk_input.shape
    mad = mean_absolute_difference(cmyk_input, decoded)
    assert 0 < mad < 2, mad
