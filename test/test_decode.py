import glob
import os.path as pt
import threading
import time

import numpy as np
import pytest
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
        height, width, _, _ = simplejpeg.decode_jpeg_header(data)
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


def test_decode_buffer_insufficient():
    for f, data, im in yield_reference_images():
        b = bytearray(len(im.get_flattened_data()) - 1)
        with pytest.raises(ValueError, match='too small') as excinfo:
            simplejpeg.decode_jpeg(data, buffer=b)


def test_decode_truncated():
    for f, data, im in yield_reference_images():
        with pytest.raises(ValueError, match='Premature end of JPEG file') as excinfo:
            simplejpeg.decode_jpeg(data[:-1])


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


def _colorspace_to_rgb(im, colorspace):
    ind = colorspace.index('R'), colorspace.index('G'), colorspace.index('B')
    out = np.zeros(im.shape[:2] + (3,))
    out[...] = im[:, :, ind]
    return out


def test_decode_colorspace():
    for f, data, im in yield_reference_images():
        for colorspace in ('RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR',
                           'XRGB', 'RGBA', 'BGRA', 'ABGR', 'ARGB'):
            np_im = np.array(im.convert('RGB'))
            sim = simplejpeg.decode_jpeg(data, colorspace)
            sim = _colorspace_to_rgb(sim, colorspace)
            assert mean_absolute_difference(np_im, sim) < 1, f
        np_im = np.array(im.convert('L'))[:, :, np.newaxis]
        sim = simplejpeg.decode_jpeg(data, 'GRAY')
        assert mean_absolute_difference(np_im, sim) < 1, f


def test_decode_writable():
    # unfortunately PyPy raises ValueError
    b = b'x' * (1024*1024*3)
    for f, data, im in yield_reference_images():
        with pytest.raises((BufferError, ValueError), match='writable'):
            simplejpeg.decode_jpeg(data, buffer=b)


def test_decode_resize_buffer_concurrent():
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
        except Exception as e:
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
    assert decoded_image.shape == (height, width, 3)


def test_decode_noncontiguous():
    b = np.zeros((3, 1024, 1024), dtype=np.uint8)
    for f, data, im in yield_reference_images():
        with pytest.raises(ValueError, match='contiguous'):
            simplejpeg.decode_jpeg(data, buffer=b.transpose((1, 2, 0)))


def test_decode_cmyk():
    for name in ('peppers_cmyk.jpg', 'cat_cmyk.jpg'):
        path = pt.join(ROOT, 'images', name)
        with open(path, 'rb') as fp:
            data = fp.read()
        height, width, colorspace, subsampling = simplejpeg.decode_jpeg_header(data)
        assert colorspace == 'CMYK' and subsampling == '444', name
        sim = simplejpeg.decode_jpeg(data, 'cmyk')
        assert sim.shape == (height, width, 4)
        with Image.open(path) as im:
            ref = 255 - np.asarray(im)
        assert mean_absolute_difference(ref, sim) < 0.5, name


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


def test_decode_cmyk_alpha():
    for name in ('peppers_cmyk.jpg', 'cat_cmyk.jpg'):
        with open(pt.join(ROOT, 'images', name), 'rb') as fp:
            data = fp.read()
        cmyk = simplejpeg.decode_jpeg(data, 'cmyk')
        for colorspace in ('RGBA', 'BGRA', 'ABGR', 'ARGB'):
            sim = simplejpeg.decode_jpeg(data, colorspace)
            np.testing.assert_array_equal(
                sim, _cmyk_reference(cmyk, colorspace), name
            )


def test_decode_cmyk_gray():
    for name in ('peppers_cmyk.jpg', 'cat_cmyk.jpg'):
        with open(pt.join(ROOT, 'images', name), 'rb') as fp:
            data = fp.read()
        cmyk = simplejpeg.decode_jpeg(data, 'cmyk')
        sim = simplejpeg.decode_jpeg(data, 'gray')
        k = cmyk[..., 3].astype(np.int32)
        channels = [
            k - ((255 - cmyk[..., i].astype(np.int32)) * k >> 8)
            for i in range(3)
        ]
        luma = ((4899 * channels[0] + 9617 * channels[1]
                 + 1868 * channels[2] + 8192) >> 14).astype(np.uint8)
        np.testing.assert_array_equal(sim[..., 0], luma, name)


def test_decode_cmyk_rgb():
    for name in ('peppers_cmyk.jpg', 'cat_cmyk.jpg'):
        data = open(pt.join(ROOT, 'images', name), 'rb').read()
        sim = simplejpeg.decode_jpeg(data, 'rgb')
        with Image.open(pt.join(ROOT, 'images', name)) as im:
            ref = np.asarray(im.convert('RGB'))
        assert mean_absolute_difference(ref, sim) < 2, name
