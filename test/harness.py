"""
Shared fixtures and helpers for the test modules.
"""

import array
import sys
import weakref
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


def _weakref(output):
    """
    A weak reference to output, or a dummy that reports it as released
    when the type cannot carry one (bytes, str).
    """
    try:
        return weakref.ref(output)
    except TypeError:
        return lambda: None


def _refcounts(supplied):
    # only used for before/after differentials: any per-interpreter
    # offset of sys.getrefcount (its own argument temporary, loop
    # bindings that hold or not) cancels between the two measurements
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


def _assert_released(values, reference):
    """
    Assert that the refcount of the given values matches the given reference values.
    Additionally, for mutable types array.array and bytearray, check whether they
    can be mutated without issue.
    """
    after = _refcounts(values)
    for value, baseline, refcount in zip(values, reference, after):
        if isinstance(value, (array.array, bytearray)):
            value.append(0)
        assert refcount == baseline, f'refcount to {type(value)!r} increased'


def assert_released_after_call(operation, *inputs):
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
    outputs = operation(*inputs)
    # verify we did not hold onto references of created outputs
    outputs = _deduplicate_values(outputs, inputs)
    # a weak reference outlives the object only if someone else kept it:
    # when this tuple is the sole holder, deleting it must kill the
    # output: every interpreter, every getrefcount convention
    output = None
    survivors = []
    for output in outputs:
        survivors.append(_weakref(output))
    # the loop variable still holds the last iterated output: drop it
    # before the assertion, it would keep the last output alive
    del output
    del outputs
    assert all(s() is None for s in survivors), 'an output outlived the call'
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
