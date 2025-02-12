from ._jpeg import encode_jpeg, encode_jpeg_yuv_planes
from ._jpeg import decode_jpeg
from ._jpeg import decode_jpeg_header


__version__ = '1.8.2'
__version_info__ = __version__.split('.')


def is_jpeg(data):
    """
    Check whether a bytes object (or similar) contains JPEG (JFIF) data.
    Returns False for truncated files.

    :param data: JPEG (JFIF) data
    :return: True if JPEG
    """
    return data[:2] == b'\xFF\xD8' and data[-2:] == b'\xFF\xD9'


__all__ = [
    decode_jpeg,
    decode_jpeg_header,
    encode_jpeg,
    encode_jpeg_yuv_planes,
    is_jpeg,
]
