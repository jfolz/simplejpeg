import os.path as pt

import numpy as np
import pytest
from harness import (
    assert_released_after_call,
    assert_released_after_error,
    generate_image,
    mean_absolute_difference,
)

import simplejpeg

ROOT = pt.abspath(pt.dirname(__file__))


def test_decode():
    im = generate_image(173, 251)
    encoded = simplejpeg.encode_jpeg(im, 98)
    decoded = simplejpeg.decode_jpeg(encoded)
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_decode_subsampling():
    im = generate_image(197, 227)
    for subsampling, delta in (('422', 2), ('420', 3), ('440', 3), ('411', 9)):
        encoded = simplejpeg.encode_jpeg(im, 98, colorsubsampling=subsampling)
        decoded = simplejpeg.decode_jpeg(encoded)
        assert 0 < mean_absolute_difference(im, decoded) < delta, subsampling


def test_fastdct():
    im = generate_image(127, 131)
    encoded_fast = simplejpeg.encode_jpeg(im, 98, fastdct=True)
    decoded_fast = simplejpeg.decode_jpeg(encoded_fast)
    assert 0 < mean_absolute_difference(im, decoded_fast) < 2


def test_grayscale():
    im = generate_image(89, 83, 1)
    encoded = simplejpeg.encode_jpeg(im, 98, colorspace='gray')
    decoded = simplejpeg.decode_jpeg(encoded, 'gray')
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_grayscale_newaxis():
    im = generate_image(589, 486, 1)
    # make array 2D
    im = im[:, :, 0]
    # add back a channel axis with newaxis
    im = im[:, :, np.newaxis]
    encoded = simplejpeg.encode_jpeg(im, 98, colorspace='gray')
    decoded = simplejpeg.decode_jpeg(encoded, 'gray')
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_colorspace():
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


def test_noncontiguous():
    im = np.zeros((3, 123, 235), dtype=np.uint8)
    with pytest.raises(ValueError, match='contiguous rows'):
        simplejpeg.encode_jpeg(im.transpose((1, 2, 0)))


def test_decode_padding_start():
    im = generate_image(233, 307)
    # make an image that has padding bytes at the start of each row
    im = im[:, 116:, :]
    encoded = simplejpeg.encode_jpeg(im, 98)
    decoded = simplejpeg.decode_jpeg(encoded)
    assert decoded.shape == (233, 191, 3)
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_decode_padding_end():
    im = generate_image(233, 307)
    # make an image that has padding bytes at the end of each row
    im = im[:, :191, :]
    encoded = simplejpeg.encode_jpeg(im, 98)
    decoded = simplejpeg.decode_jpeg(encoded)
    assert decoded.shape == (233, 191, 3)
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_decode_padding_both():
    im = generate_image(233, 307)
    # make an image that has padding bytes at the start and end of each row
    im = im[:, 89:192, :]
    encoded = simplejpeg.encode_jpeg(im, 98)
    decoded = simplejpeg.decode_jpeg(encoded)
    assert decoded.shape == (233, 103, 3)
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_decode_tiny():
    # smol image less than one MCU (8x8 for gray, 16x16 for subsampled color)
    im = generate_image(7, 13)
    encoded = simplejpeg.encode_jpeg(im, 98)
    decoded = simplejpeg.decode_jpeg(encoded)
    assert decoded.shape == (7, 13, 3)
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_2d():
    im = np.zeros((589, 486), dtype=np.uint8)
    with pytest.raises(ValueError, match='wrong number of dimensions'):
        simplejpeg.encode_jpeg(im, 98, colorspace='gray')


def test_broadcast_row():
    width, height, channels = 593, 132, 3
    im = np.zeros((width, channels), dtype=np.uint8)
    im = im[np.newaxis, :, :]
    im = np.broadcast_to(im, (height, width, channels))
    with pytest.raises(ValueError, match='broadcasting rows is not supported'):
        simplejpeg.encode_jpeg(im, 98, colorspace='rgb')


def test_cmyk():
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


def test_buffers_released_rgb():
    # the exported input is only held for the duration of the call: a
    # reference kept after the call shows up in the refcount
    im = generate_image(33, 47, 3)

    def encode(image):
        return simplejpeg.encode_jpeg(image, 98)

    assert_released_after_call(encode, im)


def test_buffers_released_gray():
    im = generate_image(33, 47, 1)

    def encode(image):
        return simplejpeg.encode_jpeg(image, 98, colorspace='gray')

    assert_released_after_call(encode, im)


def test_buffers_released_flipud():
    # the flipud view fails inside the compressor and its message comes
    # from libjpeg, not worth pinning
    im = generate_image(33, 47, 3)
    flipped = np.flipud(im)

    def encode(image):
        return simplejpeg.encode_jpeg(image, 98)

    assert_released_after_error(encode, flipped)


def test_buffers_released_channels():
    im = generate_image(33, 47, 3)
    channels = np.resize(im, (im.shape[0], im.shape[1], 2))

    def encode(image):
        return simplejpeg.encode_jpeg(image, 98)

    assert_released_after_error(encode, channels, match='channels does not match')


def test_buffers_released_strided():
    strided = np.zeros((3, 33, 47), dtype=np.uint8).transpose((1, 2, 0))

    def encode(image):
        return simplejpeg.encode_jpeg(image, 98)

    assert_released_after_error(encode, strided, match='contiguous rows')


def test_buffers_released_broadcast():
    im = generate_image(33, 47, 3)
    broadcast = np.broadcast_to(im[0], im.shape)

    def encode(image):
        return simplejpeg.encode_jpeg(image, 98)

    assert_released_after_error(encode, broadcast, match='broadcasting rows is not supported')


def test_buffers_released_2d():
    # a 2-D image does not fit the 3-D buffer signature
    flat = np.zeros((33, 47), dtype=np.uint8)

    def encode(image):
        return simplejpeg.encode_jpeg(image, 98, colorspace='gray')

    assert_released_after_error(encode, flat, match='wrong number of dimensions')
