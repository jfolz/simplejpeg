from typing import List
from ._jpeg import decode_jpeg as decode_jpeg
from ._jpeg import decode_jpeg_header as decode_jpeg_header
from ._jpeg import encode_jpeg as encode_jpeg
from ._jpeg import encode_jpeg_yuv_planes as encode_jpeg_yuv_planes

__version__: str
__version_info__: List[str]

def is_jpeg(data: bytes) -> bool: ...
