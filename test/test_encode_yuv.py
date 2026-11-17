import numpy as np
import pytest

from numpy.lib.stride_tricks import sliding_window_view

import simplejpeg


def mean_absolute_difference(a, b):
    return np.abs(a.astype(np.float32) - b.astype(np.float32)).mean()


def _box_blur(image, radius):
    # soften the block edges of the synthetic image so that chroma
    # subsampling behaves like on natural images
    padded = np.pad(image, [(radius, radius), (radius, radius), (0, 0)],
                    mode='edge').astype(np.float32)
    return sliding_window_view(padded, (2*radius + 1, 2*radius + 1),
                               axis=(0, 1)).mean(axis=(-1, -2))


def _downsample(channel, horizontal, vertical):
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
    # JFIF BT.601 full-range conversion as used for encoding JPEGs
    r = rgb[..., 0].astype(np.float32)
    g = rgb[..., 1].astype(np.float32)
    b = rgb[..., 2].astype(np.float32)
    y = np.rint(0.299 * r + 0.587 * g + 0.114 * b).astype(np.uint8)
    cb = np.rint(128 - 0.168736 * r - 0.331264 * g + 0.5 * b).astype(np.uint8)
    cr = np.rint(128 + 0.5 * r - 0.418688 * g - 0.081312 * b).astype(np.uint8)
    Y = np.ascontiguousarray(y)
    U = np.ascontiguousarray(_downsample(cb, horizontal, vertical))
    V = np.ascontiguousarray(_downsample(cr, horizontal, vertical))
    return Y, U, V


def generate_image(width=800, height=600):
    rng = np.random.default_rng(9)
    # blocks of constant color reduce the amount of high frequency noise,
    # which makes encoding with chroma subsampling less lossy
    rgb = rng.integers(
        0, 255, (-(-height // 8), -(-width // 8), 3), dtype=np.uint8,
    )
    rgb = rgb.repeat(8, axis=0)[:height].repeat(8, axis=1)[:width]
    rgb = _box_blur(rgb, 6)
    return np.ascontiguousarray(np.rint(rgb).astype(np.uint8)), width, height


def encode_decode_gray(padding_start, padding_end, delta, width=800):
    gray, width, _ = generate_image()
    gray = gray.mean(axis=2, dtype=np.uint8)
    left = padding_start
    right = width-padding_end
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
    rgb, width, height = generate_image()
    left = padding_start*horizontal
    right = width-padding_end*horizontal-luma_padding_horizontal
    bottom = height-luma_padding_vertical
    cropped_rgb = rgb[:bottom, left:right, :]
    Y, U, V = rgb_to_yuv_planes(rgb, horizontal, vertical)
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


def test_encode_yuv_noncontiguous_Y():
    encode_yuv_noncontiguous(0, 2, 50, 1, 50, 1)


def test_encode_yuv_noncontiguous_U():
    encode_yuv_noncontiguous(50, 1, 0, 2, 50, 1)


def test_encode_yuv_noncontiguous_V():
    encode_yuv_noncontiguous(50, 1, 50, 1, 0, 2)


def test_encode_yuv_missing_U():
    width, height = 100, 100
    Y, _, V = np.zeros((3, height, width), dtype=np.uint8)
    with pytest.raises(ValueError, match=r'U \(missing\) and V \(present\)'):
        simplejpeg.encode_jpeg_yuv_planes(Y, None, V)


def test_encode_yuv_missing_V():
    width, height = 100, 100
    Y, U, _ = np.zeros((3, height, width), dtype=np.uint8)
    with pytest.raises(ValueError, match=r'U \(present\) and V \(missing\)'):
        simplejpeg.encode_jpeg_yuv_planes(Y, U, None)


def test_encode_yuv_1d_Y():
    Y, U, V = np.zeros((3, 400, 300), dtype=np.uint8)
    with pytest.raises(ValueError, match='wrong number of dimensions'):
        simplejpeg.encode_jpeg_yuv_planes(Y[:,0], U, V, 98)


def test_encode_yuv_1d_U():
    Y, U, V = np.zeros((3, 400, 300), dtype=np.uint8)
    with pytest.raises(ValueError, match='wrong number of dimensions'):
        simplejpeg.encode_jpeg_yuv_planes(Y, U[:,0], V, 98)


def test_encode_yuv_1d_V():
    Y, U, V = np.zeros((3, 400, 300), dtype=np.uint8)
    with pytest.raises(ValueError, match='wrong number of dimensions'):
        simplejpeg.encode_jpeg_yuv_planes(Y, U, V[:,0], 98)


def _broadcast_rows(arr):
    return np.broadcast_to(arr[0, ...], arr.shape)


def test_encode_yuv_broadcast_row_Y():
    Y, U, V = np.zeros((3, 593, 132), dtype=np.uint8)
    Y = _broadcast_rows(Y)
    with pytest.raises(ValueError, match='broadcasting Y plane rows is not supported'):
        simplejpeg.encode_jpeg_yuv_planes(Y, U, V, 98)


def test_encode_yuv_broadcast_row_U():
    Y, U, V = np.zeros((3, 593, 132), dtype=np.uint8)
    U = _broadcast_rows(U)
    with pytest.raises(ValueError, match='broadcasting U plane rows is not supported'):
        simplejpeg.encode_jpeg_yuv_planes(Y, U, V, 98)


def test_encode_yuv_broadcast_row_V():
    Y, U, V = np.zeros((3, 593, 132), dtype=np.uint8)
    V = _broadcast_rows(V)
    with pytest.raises(ValueError, match='broadcasting V plane rows is not supported'):
        simplejpeg.encode_jpeg_yuv_planes(Y, U, V, 98)
