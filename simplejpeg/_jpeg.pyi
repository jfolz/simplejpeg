from typing import Any
from typing import Text
from typing import Tuple
from typing import SupportsInt
from typing import SupportsFloat
import numpy as np


def decode_jpeg_header(
        data: Any,
        min_height: SupportsInt=0,
        min_width: SupportsInt=0,
        min_factor: SupportsFloat=1,
        strict: bool=True,
) -> Tuple[SupportsInt, SupportsInt, Text, Text]:
    """
    Decode the header of a JPEG image.
    Returns height and width in pixels
    and colorspace and subsampling as string.

    Parameters:
        data: JPEG data
        min_height: height should be >= this minimum
                    height in pixels; values <= 0 are ignored
        min_width: width should be >= this minimum
                   width in pixels; values <= 0 are ignored
        min_factor: minimum scaling factor when decoding to smaller
                    ize; factors smaller than 2 may take longer to
                    decode; default 1
        strict: if True, raise ValueError for recoverable errors;
                default True

    Returns:
        height, width, colorspace, color subsampling
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
        strict: bool=True,
) -> np.ndarray:
    """
    Decode a JPEG (JFIF) string.
    Returns a numpy array.

    Parameters:
        data: JPEG data
        colorspace: target colorspace, any of the following:
                   'RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR', 'XRGB',
                   'GRAY', 'RGBA', 'BGRA', 'ABGR', 'ARGB';
                   'CMYK' may be used for images already in CMYK space.
        fastdct: If True, use fastest DCT method;
                 speeds up decoding by 4-5% for a minor loss in quality
        fastupsample: If True, use fastest color upsampling method;
                      speeds up decoding by 4-5% for a minor loss
                      in quality
        min_height: height should be >= this minimum in pixels;
                    values <= 0 are ignored
        min_width: width should be >= this minimum in pixels;
                   values <= 0 are ignored
        min_factor: minimum scaling factor (original size / decoded size);
                    factors smaller than 2 may take longer to decode;
                    default 1
        buffer: use given object as output buffer;
                must support the buffer protocol and be writable, e.g.,
                numpy ndarray or bytearray;
                use decode_jpeg_header to find out required minimum size
                if image dimensions are unknown
        strict: if True, raise ValueError for recoverable errors;
                default True

    Returns:
        image as numpy array
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

    Parameters:
        image: uncompressed image as uint8 array
        quality: JPEG quantization factor
        colorspace: source colorspace; one of
                   'RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR', 'XRGB',
                   'GRAY', 'RGBA', 'BGRA', 'ABGR', 'ARGB', 'CMYK'.
        colorsubsampling: subsampling factor for color channels; one of
                          '444', '422', '420', '440', '411', 'Gray'.
        fastdct: If True, use fastest DCT method;
                 speeds up encoding by 4-5% for a minor loss in quality

    Returns:
        encoded image as JPEG (JFIF) data
    """
    return b''
