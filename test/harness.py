"""
Shared fixtures and helpers for the test modules.
"""

import sys

import numpy as np
import pytest
from numpy.lib.stride_tricks import sliding_window_view


def mean_absolute_difference(a, b):
    return np.abs(a.astype(np.float32) - b.astype(np.float32)).mean()


def _box_blur(image, radius):
    # soften the block edges of the synthetic image so that encoding with
    # chroma subsampling behaves like on natural images; the box filter is
    # separable: two 1-D passes cost O(H*W*k) instead of O(H*W*k^2)
    k = 2 * radius + 1
    padded = np.pad(image, [(radius, radius), (radius, radius), (0, 0)],
                    mode='edge').astype(np.float32)
    out = sliding_window_view(padded, (1, k), axis=(0, 1)).mean(axis=(-1, -2))
    return sliding_window_view(out, (k, 1), axis=(0, 1)).mean(axis=(-1, -2))


def generate_image(height=800, width=600, channels=3):
    rng = np.random.default_rng(9)
    # blocks of constant color reduce the amount of high frequency noise,
    # which makes encoding with chroma subsampling less lossy
    arr = rng.integers(
        0, 255, (max(1, -(-height // 8)), max(1, -(-width // 8)), channels),
        dtype=np.uint8,
    )
    arr = arr.repeat(8, axis=0)[:height].repeat(8, axis=1)[:, :width]
    arr = _box_blur(arr, 6)
    return np.ascontiguousarray(np.rint(arr).astype(np.uint8))


def _refcounts(supplied):
    return tuple(sys.getrefcount(buffer) for buffer in supplied)


def _fresh_outputs(result):
    # the freshly created outputs worth checking: scalars and small
    # integers may be interned and are not fresh themselves
    return tuple(o for o in (result if isinstance(result, tuple)
                             else (result,))
                 if isinstance(o, (bytes, bytearray, np.ndarray)))


def _fresh_refcount():
    # calibrate the refcount a freshly created output measures when only
    # the caller holds it: the holder structure mirrors the release check
    # exactly (result name, filtered tuple, measurement binding), and
    # freshly created bytes and ndarray must measure the same
    counts = []
    for fresh in (lambda: bytes(bytearray(b'fresh output')),
                  lambda: np.zeros((2, 3), np.uint8)):
        result = fresh()
        fresh_tuple = _fresh_outputs(result)
        counts.append(_refcounts(fresh_tuple)[0])
    assert counts[0] == counts[1], counts
    return counts[0]


def _assert_released(supplied, baselines):
    # a still held bytearray export refuses the post-call resize with a
    # BufferError, a still held ndarray reference shows up in the
    # refcount; after is measured with the same helper as the baseline so
    # that the measurement of one buffer cannot inflate another
    after = _refcounts(supplied)
    for buffer, baseline, refcount in zip(supplied, baselines, after):
        if isinstance(buffer, bytearray):
            buffer += b'\x00'
        else:
            assert refcount == baseline, f'a reference to {type(buffer)!r} survived the call'


def assert_released_after_call(operation, *inputs):
    """
    Run operation(*inputs) and verify that:

        1. Refcount on inputs does not increase
        2. Refcount of result is identical to a freshly created object.
           A bytearray input must resize without BufferError.
    """
    before = _refcounts(inputs)
    result = operation(*inputs)
    fresh = _fresh_outputs(result)
    if fresh:
        margins = _refcounts(fresh)
        assert margins == (_fresh_refcount(),) * len(fresh), f'the operation kept a reference to the returned output: {margins!r}'
    # drop results in case they reference inputs,
    # e.g. ndarray referencing an output buffer
    del result, fresh
    _assert_released(inputs, before)


def assert_released_after_error(operation, *inputs, error=ValueError, match=None):
    """
    Like assert_released_after_call, but the operation is expected to
    raise the given error class, with or without the pinned message.
    """
    before = _refcounts(inputs)
    with pytest.raises(error, match=match):
        operation(*inputs)
    _assert_released(inputs, before)
