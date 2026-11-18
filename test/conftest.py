# Shared pytest configuration: ft gating for GIL-related tests.
"""Suite-wide fixtures and markers.

GIL-related tests reference the ``free_threaded`` marker; the gate itself is
applied once here instead of being re-implemented per test file.
"""

import ctypes
import re
import sys
import sysconfig

import pytest


def _is_free_threaded_build():
    # check config whether this is a free-threaded build:
    # 1. sys.version says so
    # 2. Py_GIL_DISABLED config var is set
    # 3. build tag says so
    #
    # sys._is_gil_enabled() cannot be used in case an incompatible import
    # has already re-enabled it
    suffix = sysconfig.get_config_var('EXT_SUFFIX') or ''
    return 'free-threading build' in sys.version \
        or sysconfig.get_config_var('Py_GIL_DISABLED') == 1 \
        or re.search(r'(?:cpython|cp)[3-9]\d+t', suffix) is not None


def _rss_bytes():
    """Working set of the current process, None when not measurable."""
    if sys.platform == 'win32':
        class MEMORY_COUNTERS(ctypes.Structure):
            _fields_ = [
                ('cb', ctypes.c_uint32),
                ('page_faults', ctypes.c_uint32),
                ('peak_working_set', ctypes.c_size_t),
                ('working_set', ctypes.c_size_t),
                ('quota_peak_paged_pool', ctypes.c_size_t),
                ('quota_paged_pool', ctypes.c_size_t),
                ('quota_peak_non_paged_pool', ctypes.c_size_t),
                ('quota_non_paged_pool', ctypes.c_size_t),
                ('pagefile', ctypes.c_size_t),
                ('peak_pagefile', ctypes.c_size_t),
            ]

        counters = MEMORY_COUNTERS()
        counters.cb = ctypes.sizeof(counters)
        process = ctypes.windll.kernel32.GetCurrentProcess()
        if not ctypes.windll.psapi.GetProcessMemoryInfo(
                process, ctypes.byref(counters), counters.cb):
            return None
        return counters.working_set
    import resource
    maxrss = resource.getrusage(resource.RUSAGE_SELF).ru_maxrss
    if sys.platform == 'darwin':
        return maxrss
    return maxrss * 1024


@pytest.fixture
def rss():
    """
    Yield a callable that returns the current working set in bytes, so
    that tests can sample the working set between battery runs. Skips
    the test when the working set is not measurable.
    """
    if _rss_bytes() is None:
        pytest.skip('no working set measurement available')
    return _rss_bytes


def pytest_configure(config):
    config.addinivalue_line(
        'markers',
        'free_threaded: requires a free-threaded Python build; skipped on '
        'GIL builds',
    )


def pytest_collection_modifyitems(config, items):
    skip = pytest.mark.skipif(
        not _is_free_threaded_build(),
        reason='requires a free-threaded Python build',
    )
    for item in items:
        if 'free_threaded' in item.keywords:
            item.add_marker(skip)
