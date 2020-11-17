from ._jpeg import encode_jpeg
from ._jpeg import decode_jpeg
from ._jpeg import decode_jpeg_header


__version__ = '1.4.0'
__version_info__ = __version__.split('.')


def is_jpeg(data):
    """
    Check whether a bytes object (or similar) contains JPEG (JFIF) data.

    :param data: JPEG (JFIF) data
    :return: True if JPEG
    """
    return data[:4] == b'\xFF\xD8\xFF\xE0'


__all__ = [
    decode_jpeg,
    decode_jpeg_header,
    encode_jpeg,
    is_jpeg,
]
