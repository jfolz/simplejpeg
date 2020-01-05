import glob
import os.path as pt

import numpy as np
from PIL import Image

import simplejpeg


ROOT = pt.abspath(pt.dirname(__file__))


def mean_absolute_difference(a, b):
    return np.abs(a.astype(np.float32) - b.astype(np.float32)).mean()


def yield_reference_images():
    image_dir = pt.join(ROOT, 'images', '*.jpg')
    for image_path in glob.iglob(image_dir):
        with open(image_path, 'rb') as fp:
            yield pt.basename(image_path), fp.read(), Image.open(image_path)


def test_decode_header():
    for f, data, im in yield_reference_images():
        height, width, colorspace, subsampling = simplejpeg.decode_jpeg_header(data)
        assert width == im.size[0] and height == im.size[1], f


def test_decode_rgb():
    for f, data, im in yield_reference_images():
        im = np.array(im.convert('RGB'))
        sim = simplejpeg.decode_jpeg(data)
        assert mean_absolute_difference(im, sim) < 1, f


def test_decode_gray():
    for f, data, im in yield_reference_images():
        im = np.array(im.convert('L'))[:, :, np.newaxis]
        sim = simplejpeg.decode_jpeg(data, 'gray')
        assert mean_absolute_difference(im, sim) < 1, f


def test_decode_buffer():
    b = bytearray(1024*1024*3)
    for f, data, im in yield_reference_images():
        im = np.array(im.convert('RGB'))
        sim = simplejpeg.decode_jpeg(data, buffer=b)
        assert mean_absolute_difference(im, sim) < 1, f


def test_decode_fastdct():
    for f, data, im in yield_reference_images():
        im = np.array(im.convert('RGB'))
        sim = simplejpeg.decode_jpeg(data, fastdct=True)
        assert mean_absolute_difference(im, sim) < 1.5, f


def test_decode_fastupsample():
    for f, data, im in yield_reference_images():
        im = np.array(im.convert('RGB'))
        sim = simplejpeg.decode_jpeg(data, fastupsample=True)
        assert mean_absolute_difference(im, sim) < 1.5, f


def test_decode_fastdct_fastupsample():
    for f, data, im in yield_reference_images():
        im = np.array(im.convert('RGB'))
        sim = simplejpeg.decode_jpeg(data, fastdct=True, fastupsample=True)
        assert mean_absolute_difference(im, sim) < 2, f


def test_decode_min_width_height():
    for f, data, im in yield_reference_images():
        w, h = im.size
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
