import os.path as pt

import numpy as np
import pytest
from harness import generate_image, mean_absolute_difference

import simplejpeg

ROOT = pt.abspath(pt.dirname(__file__))


def test_encode_decode():
    im = generate_image(173, 251)
    encoded = simplejpeg.encode_jpeg(im, 98)
    decoded = simplejpeg.decode_jpeg(encoded)
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_encode_decode_subsampling():
    im = generate_image(197, 227)
    for subsampling, delta in (('422', 2), ('420', 3), ('440', 3), ('411', 9)):
        encoded = simplejpeg.encode_jpeg(im, 98, colorsubsampling=subsampling)
        decoded = simplejpeg.decode_jpeg(encoded)
        assert 0 < mean_absolute_difference(im, decoded) < delta, subsampling


def test_encode_fastdct():
    im = generate_image(127, 131)
    encoded_fast = simplejpeg.encode_jpeg(im, 98, fastdct=True)
    decoded_fast = simplejpeg.decode_jpeg(encoded_fast)
    assert 0 < mean_absolute_difference(im, decoded_fast) < 2


def test_encode_grayscale():
    im = generate_image(89, 83, 1)
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
    im = generate_image(89, 83, 4)
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
    im = generate_image(233, 307)
    # make an image that has padding bytes at the start of each row
    im = im[:, 116:, :]
    encoded = simplejpeg.encode_jpeg(im, 98)
    decoded = simplejpeg.decode_jpeg(encoded)
    assert decoded.shape == (233, 191, 3)
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_encode_decode_padding_end():
    im = generate_image(233, 307)
    # make an image that has padding bytes at the end of each row
    im = im[:, :191, :]
    encoded = simplejpeg.encode_jpeg(im, 98)
    decoded = simplejpeg.decode_jpeg(encoded)
    assert decoded.shape == (233, 191, 3)
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_encode_decode_padding_both():
    im = generate_image(233, 307)
    # make an image that has padding bytes at the start and end of each row
    im = im[:, 89:192, :]
    encoded = simplejpeg.encode_jpeg(im, 98)
    decoded = simplejpeg.decode_jpeg(encoded)
    assert decoded.shape == (233, 103, 3)
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_encode_decode_tiny():
    # smol image less than one MCU (8x8 for gray, 16x16 for subsampled color)
    im = generate_image(7, 13)
    encoded = simplejpeg.encode_jpeg(im, 98)
    decoded = simplejpeg.decode_jpeg(encoded)
    assert decoded.shape == (7, 13, 3)
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
