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


def _ensure_tuple(v):
    return v if isinstance(v, tuple) else (v,)


def _fresh_outputs(result, ignore_objects=()):
    # freshly created outputs worth checking: scalars and strings may be
    # interned and are not fresh; outputs that are one of the inputs are
    # caller-held by design and verified on the input side instead, and
    # outputs that appear more than once in the returned structure are
    # skipped altogether: their refcount carries caller-side holders that
    # do not scale predictably with the occurrence count, so a floor
    # comparison has no stable meaning for them (verified: a duplicated
    # fresh bytes measured one above the floor through its second slot)
    result = _ensure_tuple(result)
    dedup = {}
    ignore_ids = set(map(id, ignore_objects))
    for value in result:
        if id(value) not in ignore_ids and isinstance(value, (bytes, bytearray, np.ndarray)):
            dedup[id(value)] = value
    return tuple(dedup.values())


def _fresh_refcount():
    # calibrate the refcount a freshly created output measures when only
    # the checker holds it: the holder structure mirrors the use in
    # assert_released_after_call exactly (result name, filtered tuple,
    # measurement binding), and freshly created bytes and ndarray must
    # measure the same
    counts = []
    for fresh in (lambda: bytes(bytearray(b'fresh output')), lambda: np.zeros((2, 3), np.uint8)):
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

    An output that is one of the inputs itself, e.g. a returned view of an
    output buffer, is not checked here: it is legitimately caller-held
    beyond the harness and its release is verified on the input side.
    An operation must also never return the same object twice: repeated
    outputs fail the check no matter what the operation holds.
    """
    before = _refcounts(inputs)
    result = operation(*inputs)
    fresh = _fresh_outputs(result, inputs)
    if fresh:
        # this is the only moment such a claim is observable: the outputs
        # are held by the checker only (one reference on the result, one
        # on the filtered tuple, one for the measurement binding), so a
        # reference the operation kept on its own output would measure
        # one above the freshly created, caller-held calibration
        expected = (_fresh_refcount(),) * len(fresh)
        margins = _refcounts(fresh)
        assert margins == expected, (
            f'the operation kept a reference to the returned output: '
            f'{margins!r} instead of {expected!r}'
        )
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
