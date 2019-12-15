from typing import Any
from typing import Text
from typing import SupportsInt
from typing import SupportsFloat
import numpy as np


def decode_jpeg_header(
        data: Any,
        min_height: SupportsInt=0,
        min_width: SupportsInt=0,
        min_factor: SupportsFloat=1,
) -> (SupportsInt, SupportsInt, Text, Text):
    """
    Decode the header of a JPEG image.
    Returns height and width in pixels
    and colorspace and subsampling as string.

    :param data: JPEG data
    :param min_height: height should be >= this minimum
                       height in pixels; values <= 0 are ignored
    :param min_width: width should be >= this minimum
                      width in pixels; values <= 0 are ignored
    :param min_factor: minimum scaling factor when decoding to smaller
                       size; factors smaller than 2 may take longer to
                       decode; default 1
    :return: height, width, colorspace, color subsampling
    """
    return 0, 0, 'rgb', '444'


def decode_jpeg(
        data: Any,
        colorspace: Text='rgb',
        fastdct: Any=False,
        fastupsample: Any=False,
        min_height: SupportsInt=0,
        min_width: SupportsInt=0,
        min_factor: SupportsFloat=1,
        buffer: Any=None,
) -> np.ndarray:
    """
    Decode a JPEG (JFIF) string.
    Returns a numpy array.

    :param data: JPEG data
    :param colorspace: target colorspace, any of the following:
                       'RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR', 'XRGB',
                       'GRAY', 'RGBA', 'BGRA', 'ABGR', 'ARGB';
                       'CMYK' may be used for images already in CMYK space.
    :param fastdct: If True, use fastest DCT method;
                    speeds up decoding by 4-5% for a minor loss in quality
    :param fastupsample: If True, use fastest color upsampling method;
                         speeds up decoding by 4-5% for a minor loss
                         in quality
    :param min_height: height should be >= this minimum in pixels;
                       values <= 0 are ignored
    :param min_width: width should be >= this minimum in pixels;
                      values <= 0 are ignored
    :param min_factor: minimum scaling factor (original size / decoded size);
                       factors smaller than 2 may take longer to decode;
                       default 1
    :param buffer: use given object as output buffer;
                   must support the buffer protocol and be writable, e.g.,
                   numpy ndarray or bytearray;
                   use decode_jpeg_header to find out required minimum size
                   if image dimensions are unknown
    :return: image as numpy array
    """
    return np.empty((1, 1, 1))


def encode_jpeg(
        image: np.ndarray,
        quality: SupportsInt=85,
        colorspace: Text='rgb',
        colorsubsampling: Text='444',
        fastdct: Any=False,
) -> bytes:
    """
    Encode an image to JPEG (JFIF) string.
    Returns JPEG (JFIF) data.

    :param image: uncompressed image as uint8 array
    :param quality: JPEG quantization factor
    :param colorspace: source colorspace; one of
                       'RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR', 'XRGB',
                       'GRAY', 'RGBA', 'BGRA', 'ABGR', 'ARGB', 'CMYK'.
    :param colorsubsampling: subsampling factor for color channels; one of
                             '444', '422', '420', '440', '411', 'Gray'.
    :param fastdct: If True, use fastest DCT method;
                    speeds up encoding by 4-5% for a minor loss in quality
    :return: encoded image as JPEG (JFIF) data
    """
    return b''
