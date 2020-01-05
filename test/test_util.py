import os.path as pt
import glob

import simplejpeg


ROOT = pt.abspath(pt.dirname(__file__))


def yield_reference_images():
    image_dir = pt.join(ROOT, 'images', '*.jpg')
    for image_path in glob.iglob(image_dir):
        with open(image_path, 'rb') as fp:
            yield pt.basename(image_path), fp.read()


def test_is_jpeg_with_jpeg():
    for f, data in yield_reference_images():
        assert simplejpeg.is_jpeg(data), f


def test_is_jpeg_non_jpeg():
    for f, data in yield_reference_images():
        b = bytearray(data)
        b[0] = ord('I')
        assert not simplejpeg.is_jpeg(b), f
