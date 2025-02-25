import glob
import os.path as pt
import io

import numpy as np
from PIL import Image
import pytest

import simplejpeg


ROOT = pt.abspath(pt.dirname(__file__))


def decode_pil(encoded):
    return np.array(Image.open(io.BytesIO(encoded)))


def mean_absolute_difference(a, b):
    return np.abs(a.astype(np.float32) - b.astype(np.float32)).mean()


def yield_reference_images():
    image_dir = pt.join(ROOT, 'images', '*.jpg')
    for image_path in glob.iglob(image_dir):
        with open(image_path, 'rb') as fp:
            yield pt.basename(image_path), fp.read(), Image.open(image_path)


def generate_image(height=800, width=600, channels=3):
    rng = np.random.default_rng(9)
    # reduce frequency of noise to make it easier to encode with chroma subsampling
    arr = rng.integers(0, 255, (height // 8, width // 8, channels), dtype=np.uint8)
    modes = {1: 'L', 3: 'RGB', 4: 'RGBA'}
    if channels == 1:
        arr = arr[:, :, 0]
    im = Image.fromarray(arr, modes[channels])
    arr = np.array(im.resize((width, height), resample=Image.Resampling.BICUBIC))
    if arr.ndim < 3:
        arr = np.expand_dims(arr, 2)
    return arr


def test_encode_decode():
    im = generate_image(1689, 1000)
    # encode with simplejpeg, decode with Pillow
    encoded = simplejpeg.encode_jpeg(im, 98)
    decoded = decode_pil(encoded)
    assert 0 < mean_absolute_difference(im, decoded) < 2
    # encode with Pillow, decode with simplejpeg
    bio = io.BytesIO()
    pil_im = Image.fromarray(im, 'RGB')
    pil_im.save(bio, format='JPEG', quality=98, subsampling=0)
    decoded = simplejpeg.decode_jpeg(bio.getbuffer())
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_encode_decode_subsampling():
    im = generate_image(679, 657)
    for subsampling, code, delta in (('422', 1, 2), ('420', 2, 3), ('440', 1, 3), ('411', 2, 9)):
        # encode with simplejpeg, decode with Pillow
        encoded = simplejpeg.encode_jpeg(im, 98, colorsubsampling=subsampling)
        bio = io.BytesIO(encoded)
        decoded = np.array(Image.open(bio))
        assert 0 < mean_absolute_difference(im, decoded) < delta, subsampling
        # encode with Pillow, decode with simplejpeg
        bio = io.BytesIO()
        pil_im = Image.fromarray(im, 'RGB')
        pil_im.save(bio, format='JPEG', quality=98, subsampling=code)
        decoded = simplejpeg.decode_jpeg(bio.getbuffer())
        assert 0 < mean_absolute_difference(im, decoded) < delta, subsampling


def test_encode_fastdct():
    im = generate_image(345, 5448)
    # encode with simplejpeg, decode with Pillow
    encoded_fast = simplejpeg.encode_jpeg(im, 98, fastdct=True)
    decoded_fast = np.array(Image.open(io.BytesIO(encoded_fast)))
    assert 0 < mean_absolute_difference(im, decoded_fast) < 2


def _colorspace_to_rgb(im, colorspace):
    ind = colorspace.index('R'), colorspace.index('G'), colorspace.index('B')
    out = np.zeros(im.shape[:2] + (3,))
    out[...] = im[:, :, ind]
    return out


def test_encode_grayscale():
    im = generate_image(589, 486, 1)
    # encode with simplejpeg, decode with Pillow
    encoded = simplejpeg.encode_jpeg(im, 98, colorspace='gray')
    decoded = decode_pil(encoded)[:, :, np.newaxis]
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_encode_grayscale_newaxis():
    im = generate_image(589, 486, 1)
    # make array 2D
    im = im[:, :, 0]
    # add back channel axis with newaxis
    im = im[:, :, np.newaxis]
    # encode with simplejpeg, decode with Pillow
    encoded = simplejpeg.encode_jpeg(im, 98, colorspace='gray')
    decoded = decode_pil(encoded)[:, :, np.newaxis]
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_encode_colorspace():
    im = generate_image(589, 486, 4)
    for colorspace in ('RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR',
                       'XRGB', 'RGBA', 'BGRA', 'ABGR', 'ARGB'):
        np_im = np.ascontiguousarray(im[:, :, :len(colorspace)])
        # encode with simplejpeg, decode with Pillow
        encoded = simplejpeg.encode_jpeg(np_im, 98, colorspace=colorspace)
        decoded = decode_pil(encoded)
        np_im = _colorspace_to_rgb(np_im, colorspace)
        assert 0 < mean_absolute_difference(np_im, decoded) < 2


def test_encode_noncontiguous():
    im = np.zeros((3, 123, 235), dtype=np.uint8)
    with pytest.raises(ValueError, match='contiguous rows'):
        simplejpeg.encode_jpeg(im.transpose((1, 2, 0)))


def test_encode_decode_padding_start():
    im = generate_image(600, 1000)
    # Make an image that has padding bytes at the start of each row
    im = im[:, 200:, :]
    # encode with simplejpeg, decode with Pillow
    encoded = simplejpeg.encode_jpeg(im, 98)
    decoded = decode_pil(encoded)
    assert decoded.shape == (600, 800, 3)
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_encode_decode_padding_end():
    im = generate_image(600, 1000)
    # Make an image that has padding bytes at the end of each row
    im = im[:, :800, :]
    # encode with simplejpeg, decode with Pillow
    encoded = simplejpeg.encode_jpeg(im, 98)
    decoded = decode_pil(encoded)
    assert decoded.shape == (600, 800, 3)
    assert 0 < mean_absolute_difference(im, decoded) < 2


def test_encode_decode_padding_both():
    im = generate_image(600, 1000)
    # Make an image that has padding bytes at the start and end of each row
    im = im[:, 100:900, :]
    # encode with simplejpeg, decode with Pillow
    encoded = simplejpeg.encode_jpeg(im, 98)
    decoded = decode_pil(encoded)
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
