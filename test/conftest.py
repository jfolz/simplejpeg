# Shared pytest configuration: ft gating for GIL-related tests.
"""Suite-wide fixtures and markers.

GIL-related tests reference the ``free_threaded`` marker; the gate itself is
applied once here instead of being re-implemented per test file.
"""

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
