from ._jpeg import encode_jpeg
from ._jpeg import decode_jpeg
from ._jpeg import decode_jpeg_header


__version__ = '1.0.0'
__version_info__ = __version__.split('.')


def is_jpeg(data):
    return data.startswith(b'\xFF\xD8\xFF\xE0')


__all__ = [
    decode_jpeg,
    decode_jpeg_header,
    encode_jpeg,
    is_jpeg,
]
