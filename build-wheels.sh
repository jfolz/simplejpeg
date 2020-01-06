#!/bin/bash
set -e -x

# Python 2.7 and 3.4 are not supported
rm -r /opt/python/cp27*
rm -r /opt/python/cp34*

# Compile wheels
for PYBIN in /opt/python/*/bin; do
    "${PYBIN}/pip" install -U pip wheel --no-warn-script-location
    "${PYBIN}/pip" install -r build-requirements.txt
    "${PYBIN}/pip" wheel . -w wheelhouse/ --no-deps
    "${PYBIN}/pip" install .
    "${PYBIN}/pip" install -r test-requirements.txt
    cd test
    "${PYBIN}/python" -m pytest -vv
    cd ..
    "${PYBIN}/pip" install uninstall -y pip wheel
done

# Bundle external shared libraries into the wheels
for whl in wheelhouse/*.whl; do
    auditwheel repair "$whl" -w dist
done

# Install packages and test
#for PYBIN in /opt/python/*/bin/; do
#    "${PYBIN}/pip" install -r test-requirements.txt
#    "${PYBIN}/pip" install turbojpeg --no-index -f wheelhouse
#    "${PYBIN}/nosetests" -w test
#done
