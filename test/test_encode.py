import glob
import os.path as pt
import io

import numpy as np
from PIL import Image
import pytest

import simplejpeg


ROOT = pt.abspath(pt.dirname(__file__))


def mean_absolute_difference(a, b):
    return np.abs(a.astype(np.float32) - b.astype(np.float32)).mean()


def yield_reference_images():
    image_dir = pt.join(ROOT, 'images', '*.jpg')
    for image_path in glob.iglob(image_dir):
        with open(image_path, 'rb') as fp:
            yield pt.basename(image_path), fp.read(), Image.open(image_path)


def test_encode_decode():
    np.random.seed(9)
    im = np.random.randint(0, 255, (1689, 1000, 3), dtype=np.uint8)
    # encode with simplejpeg, decode with Pillow
    encoded = simplejpeg.encode_jpeg(im, 85)
    decoded = np.array(Image.open(io.BytesIO(encoded)))
    assert 0 < mean_absolute_difference(im, decoded) < 10
    # encode with Pillow, decode with simplejpeg
    bio = io.BytesIO()
    pil_im = Image.fromarray(im, 'RGB')
    pil_im.save(bio, format='JPEG', quality=85, subsampling=0)
    decoded = simplejpeg.decode_jpeg(bio.getbuffer())
    assert 0 < mean_absolute_difference(im, decoded) < 10


def test_encode_decode_subsampling():
    np.random.seed(9)
    im = np.random.randint(0, 255, (679, 657, 3), dtype=np.uint8)
    for subsampling, code in (('422', 1), ('420', 2), ('440', 1), ('411', 2)):
        # encode with simplejpeg, decode with Pillow
        encoded = simplejpeg.encode_jpeg(im, 85, colorsubsampling=subsampling)
        bio = io.BytesIO(encoded)
        decoded = np.array(Image.open(bio))
        assert 0 < mean_absolute_difference(im, decoded) < 50, subsampling
        # encode with Pillow, decode with simplejpeg
        bio = io.BytesIO()
        pil_im = Image.fromarray(im, 'RGB')
        pil_im.save(bio, format='JPEG', quality=85, subsampling=code)
        decoded = simplejpeg.decode_jpeg(bio.getbuffer())
        assert 0 < mean_absolute_difference(im, decoded) < 50, subsampling


def test_encode_fastdct():
    np.random.seed(9)
    im = np.random.randint(0, 255, (345, 5448, 3), dtype=np.uint8)
    # encode with simplejpeg, decode with Pillow
    encoded_fast = simplejpeg.encode_jpeg(im, 85, fastdct=True)
    decoded_fast = np.array(Image.open(io.BytesIO(encoded_fast)))
    assert 0 < mean_absolute_difference(im, decoded_fast) < 10


def _colorspace_to_rgb(im, colorspace):
    ind = colorspace.index('R'), colorspace.index('G'), colorspace.index('B')
    out = np.zeros(im.shape[:2] + (3,))
    out[...] = im[:, :, ind]
    return out


def test_encode_grayscale():
    np.random.seed(486943)
    im = np.random.randint(0, 255, (589, 486, 1), dtype=np.uint8)
    # encode with simplejpeg, decode with Pillow
    encoded = simplejpeg.encode_jpeg(im, 85, colorspace='gray')
    decoded = np.array(Image.open(io.BytesIO(encoded)))[:, :, np.newaxis]
    assert 0 < mean_absolute_difference(im, decoded) < 10


def test_encode_colorspace():
    np.random.seed(9)
    im = np.random.randint(0, 255, (589, 486, 4), dtype=np.uint8)
    for colorspace in ('RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR',
                       'XRGB', 'RGBA', 'BGRA', 'ABGR', 'ARGB'):
        np_im = np.ascontiguousarray(im[:, :, :len(colorspace)])
        # encode with simplejpeg, decode with Pillow
        encoded = simplejpeg.encode_jpeg(np_im, 85, colorspace=colorspace)
        decoded = np.array(Image.open(io.BytesIO(encoded)))
        np_im = _colorspace_to_rgb(np_im, colorspace)
        assert 0 < mean_absolute_difference(np_im, decoded) < 10


def test_encode_noncontiguous():
    with pytest.raises(ValueError) as exc:
        im = np.zeros((3, 123, 235), dtype=np.uint8)
        simplejpeg.encode_jpeg(im.transpose((1, 2, 0)))
    assert 'contiguous' in str(exc.value)
