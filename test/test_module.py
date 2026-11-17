import sys

import pytest


@pytest.mark.free_threaded
def test_import_does_not_enable_gil():
    # simplejpeg declares free-threading compatibility (Py_mod_gil slot);
    # importing it on a free-threaded interpreter must not turn the GIL on
    assert not sys._is_gil_enabled(), (
        'the GIL was already re-enabled before simplejpeg was imported'
    )
    import simplejpeg
    assert not sys._is_gil_enabled(), (
        'importing simplejpeg re-enabled the GIL'
    )
