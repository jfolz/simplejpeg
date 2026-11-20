import numpy as np
import pytest
from harness import (
    assert_released_after_call,
    assert_released_after_error,
    mean_absolute_difference,
)
from harness import generate_image as generate_rgb_image

import simplejpeg

RGB = generate_rgb_image(422, 436)


def _downsample(channel, horizontal, vertical):
    if horizontal == 1 and vertical == 1:
        return channel
    # average over each block of `horizontal` x `vertical` samples
    # (a box kernel with round-to-nearest, applied to pseudo-padded edges)
    height, width = channel.shape
    rh = -(-height // vertical) * vertical
    rw = -(-width // horizontal) * horizontal
    padded = np.pad(channel, [(0, rh - height), (0, rw - width)], mode='edge')
    return np.rint(
        padded.reshape(rh // vertical, vertical, rw // horizontal, horizontal)
              .mean(axis=(1, 3)),
    ).astype(np.uint8)


def rgb_to_yuv_planes(rgb, horizontal, vertical):
    r = rgb[..., 0].astype(np.int32)
    g = rgb[..., 1].astype(np.int32)
    b = rgb[..., 2].astype(np.int32)
    y = (19595 * r + 38470 * g + 7471 * b + 32768) >> 16
    cb = (32768 * b - 11059 * r - 21709 * g + 8421375) >> 16
    cr = (32768 * r - 27439 * g - 5329 * b + 8421375) >> 16
    Y = np.ascontiguousarray(y.astype(np.uint8))
    U = np.ascontiguousarray(_downsample(cb.astype(np.uint8),
                                         horizontal, vertical))
    V = np.ascontiguousarray(_downsample(cr.astype(np.uint8),
                                         horizontal, vertical))
    return Y, U, V


Y_PLANE, U_PLANE, V_PLANE = rgb_to_yuv_planes(RGB, 2, 2)


def encode_decode_gray(padding_start, padding_end, delta):
    gray = RGB.mean(axis=2, dtype=np.uint8)
    left = padding_start
    right = RGB.shape[1] - padding_end
    gray = gray[:, left:right]
    encoded = simplejpeg.encode_jpeg_yuv_planes(gray, None, None, 98)
    decoded = simplejpeg.decode_jpeg(encoded, 'gray')
    # simplejpeg returns a 3-dimensional (height, width, 1) array
    assert decoded.shape == gray.shape + (1,)
    assert 0 < mean_absolute_difference(gray, decoded[..., 0]) < delta


def test_encode_decode_yuv_gray():
    encode_decode_gray(0, 0, 1)


def test_encode_decode_yuv_gray_start():
    encode_decode_gray(45, 0, 1)


def test_encode_decode_yuv_gray_end():
    encode_decode_gray(0, 75, 1)


def test_encode_decode_yuv_gray_both():
    encode_decode_gray(24, 79, 1)


def encode_decode_yuv(
    horizontal,
    vertical,
    padding_start,
    padding_end,
    delta,
    luma_padding_horizontal=0,
    luma_padding_vertical=0,
):
    left = padding_start*horizontal
    right = RGB.shape[1]-padding_end*horizontal-luma_padding_horizontal
    bottom = RGB.shape[0]-luma_padding_vertical
    cropped_rgb = RGB[:bottom, left:right, :]
    Y, U, V = rgb_to_yuv_planes(RGB, horizontal, vertical)
    chroma_width = U.shape[1]
    Y = Y[:bottom, left:right]
    U = U[:, padding_start:chroma_width-padding_end]
    V = V[:, padding_start:chroma_width-padding_end]
    encoded = simplejpeg.encode_jpeg_yuv_planes(Y, U, V, 98)
    decoded = simplejpeg.decode_jpeg(encoded)
    assert decoded.shape == cropped_rgb.shape
    assert 0 < mean_absolute_difference(cropped_rgb, decoded) < delta


def test_encode_decode_yuv_444():
    encode_decode_yuv(1, 1, 0, 0, 2)


def test_encode_decode_yuv_444_padding_start():
    encode_decode_yuv(1, 1, 50, 0, 2)


def test_encode_decode_yuv_444_padding_end():
    encode_decode_yuv(1, 1, 0, 50, 2)


def test_encode_decode_yuv_444_padding_both():
    encode_decode_yuv(1, 1, 50, 50, 2)


def test_encode_decode_yuv_422():
    encode_decode_yuv(2, 1, 0, 0, 2)


def test_encode_decode_yuv_422_padding_start():
    encode_decode_yuv(2, 1, 50, 0, 2)


def test_encode_decode_yuv_422_padding_end():
    encode_decode_yuv(2, 1, 0, 50, 2)


def test_encode_decode_yuv_422_padding_end_odd():
    encode_decode_yuv(2, 1, 0, 50, 2, luma_padding_horizontal=1)


def test_encode_decode_yuv_422_padding_both():
    encode_decode_yuv(2, 1, 50, 50, 2)


def test_encode_decode_yuv_422_padding_both_odd():
    encode_decode_yuv(2, 1, 50, 50, 2, luma_padding_horizontal=1)


def test_encode_decode_yuv_440():
    encode_decode_yuv(1, 2, 0, 0, 2)


def test_encode_decode_yuv_440_padding_start():
    encode_decode_yuv(1, 2, 50, 0, 2)


def test_encode_decode_yuv_440_padding_end():
    encode_decode_yuv(1, 2, 0, 50, 2)


def test_encode_decode_yuv_440_padding_end_odd():
    encode_decode_yuv(1, 2, 0, 50, 2, luma_padding_vertical=1)


def test_encode_decode_yuv_440_padding_both():
    encode_decode_yuv(1, 2, 50, 50, 2)


def test_encode_decode_yuv_440_padding_both_odd():
    encode_decode_yuv(1, 2, 50, 50, 2, luma_padding_vertical=1)


def test_encode_decode_yuv_420():
    encode_decode_yuv(2, 2, 0, 0, 3)


def test_encode_decode_yuv_420_padding_start():
    encode_decode_yuv(2, 2, 50, 0, 3)


def test_encode_decode_yuv_420_padding_end():
    encode_decode_yuv(2, 2, 0, 50, 3)


def test_encode_decode_yuv_420_padding_end_odd():
    encode_decode_yuv(2, 2, 0, 50, 3, luma_padding_horizontal=1)


def test_encode_decode_yuv_420_padding_both():
    encode_decode_yuv(2, 2, 50, 50, 3)


def test_encode_decode_yuv_420_padding_both_odd():
    encode_decode_yuv(2, 2, 50, 50, 3, luma_padding_horizontal=1)


def test_encode_decode_yuv_411():
    # 411 output shows awful vertical stripes - not sure if this is normal
    encode_decode_yuv(4, 1, 0, 0, 9)


def test_encode_decode_yuv_411_padding_start():
    encode_decode_yuv(4, 1, 50, 0, 9)


def test_encode_decode_yuv_411_padding_end():
    encode_decode_yuv(4, 1, 0, 50, 9)


def test_encode_decode_yuv_411_padding_end_odd():
    encode_decode_yuv(4, 1, 0, 50, 9, luma_padding_horizontal=1)
    encode_decode_yuv(4, 1, 0, 50, 9, luma_padding_horizontal=2)
    encode_decode_yuv(4, 1, 0, 50, 9, luma_padding_horizontal=3)


def test_encode_decode_yuv_411_padding_both():
    encode_decode_yuv(4, 1, 50, 50, 9)


def test_encode_decode_yuv_411_padding_both_odd():
    encode_decode_yuv(4, 1, 50, 50, 9, luma_padding_horizontal=1)
    encode_decode_yuv(4, 1, 50, 50, 9, luma_padding_horizontal=2)
    encode_decode_yuv(4, 1, 50, 50, 9, luma_padding_horizontal=3)


def encode_yuv_noncontiguous(Ycrop, Ystride, Ucrop, Ustride, Vcrop, Vstride):
    width, height = 100, 100
    Y, U, V = np.zeros((3, height, width), dtype=np.uint8)
    Y = Y[:, :width-Ycrop:Ystride]
    U = U[:, :width-Ucrop:Ustride]
    V = V[:, :width-Vcrop:Vstride]
    with pytest.raises(ValueError, match='contiguous rows'):
        simplejpeg.encode_jpeg_yuv_planes(Y, U, V)


def test_noncontiguous_Y():
    encode_yuv_noncontiguous(0, 2, 50, 1, 50, 1)


def test_noncontiguous_U():
    encode_yuv_noncontiguous(50, 1, 0, 2, 50, 1)


def test_noncontiguous_V():
    encode_yuv_noncontiguous(50, 1, 50, 1, 0, 2)


def test_missing_U():
    width, height = 100, 100
    Y, _, V = np.zeros((3, height, width), dtype=np.uint8)
    with pytest.raises(ValueError, match=r'U \(missing\) and V \(present\)'):
        simplejpeg.encode_jpeg_yuv_planes(Y, None, V)


def test_missing_V():
    width, height = 100, 100
    Y, U, _ = np.zeros((3, height, width), dtype=np.uint8)
    with pytest.raises(ValueError, match=r'U \(present\) and V \(missing\)'):
        simplejpeg.encode_jpeg_yuv_planes(Y, U, None)


def test_1d_Y():
    Y, U, V = np.zeros((3, 400, 300), dtype=np.uint8)
    with pytest.raises(ValueError, match='wrong number of dimensions'):
        simplejpeg.encode_jpeg_yuv_planes(Y[:,0], U, V, 98)


def test_1d_U():
    Y, U, V = np.zeros((3, 400, 300), dtype=np.uint8)
    with pytest.raises(ValueError, match='wrong number of dimensions'):
        simplejpeg.encode_jpeg_yuv_planes(Y, U[:,0], V, 98)


def test_1d_V():
    Y, U, V = np.zeros((3, 400, 300), dtype=np.uint8)
    with pytest.raises(ValueError, match='wrong number of dimensions'):
        simplejpeg.encode_jpeg_yuv_planes(Y, U, V[:,0], 98)


def _broadcast_rows(arr):
    return np.broadcast_to(arr[0, ...], arr.shape)


def test_broadcast_row_Y():
    Y, U, V = np.zeros((3, 593, 132), dtype=np.uint8)
    Y = _broadcast_rows(Y)
    with pytest.raises(ValueError, match='broadcasting Y plane rows is not supported'):
        simplejpeg.encode_jpeg_yuv_planes(Y, U, V, 98)


def test_broadcast_row_U():
    Y, U, V = np.zeros((3, 593, 132), dtype=np.uint8)
    U = _broadcast_rows(U)
    with pytest.raises(ValueError, match='broadcasting U plane rows is not supported'):
        simplejpeg.encode_jpeg_yuv_planes(Y, U, V, 98)


def test_broadcast_row_V():
    Y, U, V = np.zeros((3, 593, 132), dtype=np.uint8)
    V = _broadcast_rows(V)
    with pytest.raises(ValueError, match='broadcasting V plane rows is not supported'):
        simplejpeg.encode_jpeg_yuv_planes(Y, U, V, 98)


def test_planes_released():
    # the exported planes are only held for the duration of the call: a
    # reference kept after the call shows up in the refcount
    def encode(y, u, v):
        return simplejpeg.encode_jpeg_yuv_planes(y, u, v, 98)

    assert_released_after_call(encode, Y_PLANE, U_PLANE, V_PLANE)


def test_planes_released_gray():
    gray = RGB.mean(axis=2, dtype=np.uint8)

    def encode(y):  # U and V are not passed on
        return simplejpeg.encode_jpeg_yuv_planes(y, None, None, 98)

    assert_released_after_call(encode, gray)


def test_planes_released_missing_U():
    # the refusal happens with Y and V already exported and must release
    # both on the way out
    def encode(y, u, v):  # U is not passed on
        return simplejpeg.encode_jpeg_yuv_planes(y, None, v, 98)

    assert_released_after_error(encode, Y_PLANE, U_PLANE, V_PLANE, match=r'U \(missing\) and V \(present\)')


def test_planes_released_missing_V():
    def encode(y, u, v):  # V is not passed on
        return simplejpeg.encode_jpeg_yuv_planes(y, u, None, 98)

    assert_released_after_error(encode, Y_PLANE, U_PLANE, V_PLANE, match=r'U \(present\) and V \(missing\)')


def test_planes_released_1d_U():
    def encode(y, u, v):  # only the first U column is passed on
        return simplejpeg.encode_jpeg_yuv_planes(y, u[:, 0], v, 98)

    assert_released_after_error(encode, Y_PLANE, U_PLANE, V_PLANE, match='wrong number of dimensions')


def test_planes_released_broadcast_U():
    def encode(y, u, v):  # U rows are broadcast, not passed on directly
        return simplejpeg.encode_jpeg_yuv_planes(y, _broadcast_rows(u), v, 98)

    assert_released_after_error(encode, Y_PLANE, U_PLANE, V_PLANE, match='broadcasting U plane rows is not supported')


def test_planes_released_broadcast_Y():
    def encode(y, u, v):  # Y rows are broadcast
        return simplejpeg.encode_jpeg_yuv_planes(_broadcast_rows(y), u, v, 98)

    assert_released_after_error(encode, Y_PLANE, U_PLANE, V_PLANE, match='broadcasting Y plane rows is not supported')


def test_planes_released_broadcast_V():
    def encode(y, u, v):  # V rows are broadcast
        return simplejpeg.encode_jpeg_yuv_planes(y, u, _broadcast_rows(v), 98)

    assert_released_after_error(encode, Y_PLANE, U_PLANE, V_PLANE, match='broadcasting V plane rows is not supported')


def _strided(plane):
    # same-shape view over doubled-width rows: non-unit column strides
    src = np.zeros((plane.shape[0], 1, 2 * plane.shape[1]), dtype=np.uint8)
    return src[:, 0, ::2]


def test_planes_released_strided_Y():
    def encode(y):  # encoded as grayscale, U and V are not passed on
        return simplejpeg.encode_jpeg_yuv_planes(y, None, None, 98)

    assert_released_after_error(encode, _strided(Y_PLANE), match='Y plane must have C contiguous rows')


def test_planes_released_strided_U():
    def encode(y, u, v):
        return simplejpeg.encode_jpeg_yuv_planes(y, u, v, 98)

    assert_released_after_error(encode, Y_PLANE, _strided(U_PLANE), V_PLANE, match='U plane must have C contiguous rows')


def test_planes_released_strided_V():
    def encode(y, u, v):
        return simplejpeg.encode_jpeg_yuv_planes(y, u, v, 98)

    assert_released_after_error(encode, Y_PLANE, U_PLANE, _strided(V_PLANE), match='V plane must have C contiguous rows')


def test_planes_released_1d_Y():
    def encode(y, u, v):  # only the first Y column is passed on
        return simplejpeg.encode_jpeg_yuv_planes(y[:, 0], u, v, 98)

    assert_released_after_error(encode, Y_PLANE, U_PLANE, V_PLANE, match='wrong number of dimensions')


def test_planes_released_1d_V():
    def encode(y, u, v):  # only the first V column is passed on
        return simplejpeg.encode_jpeg_yuv_planes(y, u, v[:, 0], 98)

    assert_released_after_error(encode, Y_PLANE, U_PLANE, V_PLANE, match='wrong number of dimensions')


def test_planes_released_shape_mismatch():
    def encode(y, u, v):
        return simplejpeg.encode_jpeg_yuv_planes(y, u, v[:, :-1], 98)

    assert_released_after_error(encode, Y_PLANE, U_PLANE, V_PLANE, match='U and V planes must have matching shape')


def test_planes_released_unknown_subsampling():
    # two equal-sized chroma planes whose width fits no standard
    # subsampling leave the colorsubsampling undetermined
    def encode(y, u, v):
        return simplejpeg.encode_jpeg_yuv_planes(y, u[:, :97], v[:, :97], 98)

    assert_released_after_error(encode, Y_PLANE, U_PLANE, V_PLANE, match='cannot determine chroma subsampling')
