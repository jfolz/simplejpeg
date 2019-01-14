from typing import Any
from typing import Text
from typing import SupportsInt
from typing import SupportsFloat
import numpy as np


def decode_jpeg(
        data: Any,
        colorspace: Text='rgb',
        fastdct: Any=True,
        fastupsample: Any=True,
        min_height: SupportsInt=0,
        min_width: SupportsInt=0,
        min_factor: SupportsFloat=1
) -> np.ndarray:
    return np.empty((1, 1, 1))


def decode_jpeg_header(
        data: Any,
        min_height: SupportsInt=0,
        min_width: SupportsInt=0,
        min_factor: SupportsFloat=1
) -> (SupportsInt, SupportsInt, Text, Text):
    return 0, 0, 'rgb', '444'


def encode_jpeg(
        image: np.ndarray,
        quality: SupportsInt=85,
        colorspace: Text='rgb',
        colorsubsampling: Text='444',
        fastdct: Any=True,
):
    return b''
