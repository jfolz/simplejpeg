import re
import sys
import sysconfig

import pytest


def _free_threaded_build():
    # build-level interpreter check, deliberately independent of the runtime
    # GIL state: other test modules already import simplejpeg during
    # collection, so sys._is_gil_enabled() is not a reliable skip condition
    if sysconfig.get_config_var('Py_GIL_DISABLED') in (1, '1'):
        return True
    # some platforms do not expose the config var; free-threaded builds keep
    # the ABI tag marker ('cpython-314t-…', 'cp313t-…') in the extension
    # suffix, while sys.implementation.cache_tag lost the 't' on 3.14
    suffix = sysconfig.get_config_var('EXT_SUFFIX') or ''
    return re.search(r'(?:cpython|cp)3\d+t', suffix) is not None


pytestmark = pytest.mark.skipif(
    not _free_threaded_build(),
    reason='requires a free-threaded Python build',
)


def test_import_does_not_enable_gil():
    # simplejpeg declares free-threading compatibility (Py_mod_gil slot);
    # importing it on a free-threaded interpreter must not turn the GIL on
    assert sys._is_gil_enabled() is False, (
        'the GIL was already re-enabled before simplejpeg was imported'
    )
    import simplejpeg
    assert sys._is_gil_enabled() is False, (
        'importing simplejpeg re-enabled the GIL'
    )
