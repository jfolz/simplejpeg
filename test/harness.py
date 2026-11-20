"""
Shared fixtures and helpers for the test modules.
"""

import array
import sys
from collections.abc import Collection
from typing import Any

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


def _refcounts(supplied: Collection[Any]) -> tuple[int,...]:
    """
    Return refcounts of the given list of objects.

    Important: Do not rely on absolute refcount values.
    The output can differ between platforms and/or Python versions.
    """
    return tuple(sys.getrefcount(buffer) - 1 for buffer in supplied)


def _ensure_tuple(v):
    return v if isinstance(v, tuple) else (v,)


def _deduplicate_values(
    values: Any | tuple[Any],
    ignore_objects: Collection[Any] = (),
    keep_types: tuple[type,...] = (bytes, array.array, bytearray, np.ndarray),
):
    """
    Deduplicate the given value(s).
    Optionally ignore everything in ignore_objects.
    Keep only types listed in keep_types. In particular str and int can have
    unpredictable refcounts (interning, immortalization).
    """
    ignore_ids = set(map(id, ignore_objects))
    dedup = {}
    for value in _ensure_tuple(values):
        if id(value) not in ignore_ids and isinstance(value, keep_types):
            dedup[id(value)] = value
    return tuple(dedup.values())


def _assert_released(values, reference, message='refcount to {type} increased'):
    """
    Assert that the refcount of the given values matches the given reference values.
    Additionally, for mutable types array.array and bytearray, check whether they
    can be mutated without issue.
    The failure message is a format template: {type} is replaced with the
    value's type; callers pass their own wording, e.g.
    'refcount to input increased' (a template without placeholders is
    used as-is).
    """
    after = _refcounts(values)
    for value, baseline, refcount in zip(values, reference, after):
        if isinstance(value, (array.array, bytearray)):
            value.append(0)
        assert refcount == baseline, message.format(type=type(value))


def assert_released_after_call(operation, *inputs, message='refcount to {type} increased'):
    """
    Run operation(*inputs) and verify that:

        1. Refcount on inputs does not increase
        2. Each newly-created output dies with our reference to it:
           nothing else kept it alive
        3. Input array.array and bytearray must resize without BufferError.

    Excluded are outputs that are also inputs, e.g. a view of an output
    buffer, since these naturally have higher (and unpredictable) refcounts.
    """
    # store refcounts before the operation
    before = _refcounts(inputs)
    # verify we did not hold onto references of created outputs
    outputs = operation(*inputs)
    outputs = _deduplicate_values(outputs, inputs)
    # obtain a platform and Python version specific reference values for
    # output refcount by applying exactly the same measurement to an identically
    # structured reference object
    reference = _refcounts((object(),))[0]
    for i, refcount in enumerate(_refcounts(outputs)):
        assert refcount == reference, f'expected refcount {reference} for output {i}, got {refcount}'
    # delete outputs to release references held in inputs
    del outputs, reference
    _assert_released(inputs, before, message)


def assert_released_after_error(operation, *inputs, error=ValueError, match=None,
                                message='refcount to {type} increased'):
    """
    Like assert_released_after_call, but the operation is expected to
    raise the given error class, with or without the pinned message.
    """
    before = _refcounts(inputs)
    with pytest.raises(error, match=match):
        operation(*inputs)
    _assert_released(inputs, before, message)
