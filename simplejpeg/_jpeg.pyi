from typing import Any
from typing import Text
from typing import Tuple
from typing import SupportsInt
from typing import SupportsFloat
from typing import Union


def decode_jpeg_header(
        data: Union[bytes, bytearray, memoryview, Any],
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
                    size; factors smaller than 2 may take longer to
                    decode; default 1
        strict: if True, raise ValueError for recoverable errors;
                default True

    Returns:
        height, width, colorspace, color subsampling
    """
    return 0, 0, 'rgb', '444'


def decode_jpeg(
        data: Union[bytes, bytearray, memoryview, Any],
        colorspace: Text='rgb',
        fastdct: Any=False,
        fastupsample: Any=False,
        min_height: SupportsInt=0,
        min_width: SupportsInt=0,
        min_factor: SupportsFloat=1,
        buffer: Union[bytearray, memoryview, Any]=None,
        strict: bool=True,
        output: Text='numpy',
) -> Any:
    """
    Decode a JPEG (JFIF) string.
    Returns image data in the format requested by output.

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
        output: either 'numpy' (default) or 'bytes'.
                'numpy' returns a numpy ndarray of shape
                (height, width, channels); numpy is imported lazily
                and only needs to be installed if this is used.
                'bytes' returns a plain bytearray plus its
                dimensions, without ever importing numpy.

    Returns:
        image = decode_jpeg(data)
            -> numpy ndarray (output='numpy', default)
        pixels, height, width, channels = decode_jpeg(data, output='bytes')
            -> raw byte buffer plus dimensions (output='bytes')
    """
    ...


def encode_jpeg(
        image: Union[memoryview, Any],
        quality: SupportsInt=85,
        colorspace: Text='rgb',
        colorsubsampling: Text='444',
        fastdct: Any=False,
) -> bytes:
    """
    Encode an image to JPEG (JFIF) string.
    Returns JPEG (JFIF) data.

    Parameters:
        image: uncompressed image as uint8 array; any object
               supporting the buffer protocol mapped to a 3D shape 
               (e.g., a NumPy ndarray, or a flat buffer cast to a 
               3D memoryview).
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


def encode_jpeg_yuv_planes(
        Y: Union[memoryview, Any],
        U: Union[memoryview, Any],
        V: Union[memoryview, Any],
        quality: SupportsInt=85,
        fastdct: Any=False,
) -> bytes:
    """
    Encode an image in a YUV planar format to JPEG (JFIF) string.
    U and V planes may be None to encode grayscale, but if one is given,
    the other must be as well.
    Returns JPEG (JFIF) data.

    Parameters:
        Y: uncompressed Y plane of the YUV image as uint8 array;
           must be a 2D shape (e.g., 2D memoryview or NumPy ndarray).
        U: uncompressed U plane of the YUV image as uint8 array;
           must be a 2D shape (e.g., 2D memoryview or NumPy ndarray).
        V: uncompressed V plane of the YUV image as uint8 array;
           must be a 2D shape (e.g., 2D memoryview or NumPy ndarray).
        quality: JPEG quantization factor
        fastdct: If True, use fastest DCT method;
                 speeds up encoding by 4-5% for a minor loss in quality

    Returns:
        encoded image as JPEG (JFIF) data
    """
    return b''
