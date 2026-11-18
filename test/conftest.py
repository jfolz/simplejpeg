# Shared pytest configuration: ft gating for GIL-related tests.
"""Suite-wide fixtures and markers.

GIL-related tests reference the ``free_threaded`` marker; the gate itself is
applied once here instead of being re-implemented per test file.
"""

import array
import ctypes
import os
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
    """
    Current resident set of this process in bytes, matching the
    psutil.Process().memory_info().rss functionality on each platform:

    - psutil itself when it is importable
    - linux: the resident field of /proc/<pid>/statm x page size
    - windows: GetProcessMemoryInfo().WorkingSetSize
    - macos: proc_pidinfo(PROC_PIDTASKINFO).pti_resident_size through
      libproc; getrusage.ru_maxrss cannot be used as a fallback since
      it is a high-water mark that cannot register growth during the
      run, which would make leak detection insensitive once any earlier
      test inflated the peak

    Returns None when the current value is not measurable.
    """
    try:
        import psutil
        return psutil.Process().memory_info().rss
    except ImportError:
        pass
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
    if sys.platform == 'darwin':
        class PROC_TASKINFO(ctypes.Structure):
            _fields_ = [
                ('pti_virtual_size', ctypes.c_uint64),
                ('pti_resident_size', ctypes.c_uint64),
                ('pti_total_user', ctypes.c_uint64),
                ('pti_total_system', ctypes.c_uint64),
                ('pti_threads_user', ctypes.c_uint64),
                ('pti_threads_system', ctypes.c_uint64),
                ('pti_policy', ctypes.c_int32),
                ('pti_faults', ctypes.c_int32),
                ('pti_pageins', ctypes.c_int32),
                ('pti_cow_faults', ctypes.c_int32),
                ('pti_messages_sent', ctypes.c_int32),
                ('pti_messages_received', ctypes.c_int32),
                ('pti_syscalls_mach', ctypes.c_int32),
                ('pti_syscalls_unix', ctypes.c_int32),
                ('pti_csw', ctypes.c_int32),
                ('pti_threadnum', ctypes.c_int32),
                ('pti_numrunning', ctypes.c_int32),
                ('pti_priority', ctypes.c_int32),
            ]

        libc = ctypes.CDLL(None)  # libSystem, includes libproc
        if not hasattr(libc, 'proc_pidinfo'):
            return None
        libc.proc_pidinfo.argtypes = (
            ctypes.c_int, ctypes.c_int, ctypes.c_uint64,
            ctypes.c_void_p, ctypes.c_int,
        )
        info = PROC_TASKINFO()
        if libc.proc_pidinfo(
                os.getpid(), 4, 0, ctypes.byref(info),
                ctypes.sizeof(info)) != ctypes.sizeof(info):
            return None
        return info.pti_resident_size
    with open(f'/proc/{os.getpid()}/statm') as f:
        return int(f.readline().split()[1]) * os.sysconf('SC_PAGE_SIZE')


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
