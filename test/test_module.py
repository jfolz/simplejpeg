import sys

import pytest


@pytest.mark.free_threaded
def test_import_does_not_enable_gil():
    # for the test to work the GIL must be disabled initially
    assert not sys._is_gil_enabled(), (
        'the GIL was already re-enabled before simplejpeg was imported'
    )
    # import simplejpeg and check if the GIL gets re-enabled
    import simplejpeg  # noqa: F401
    assert not sys._is_gil_enabled(), (
        'importing simplejpeg re-enabled the GIL'
    )
