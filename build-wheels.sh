#!/bin/bash
set -e -x

# Python 2.7 and 3.4 are not supported
rm -r /opt/python/cp27*
rm -r /opt/python/cp34*

# Compile wheels
for PYBIN in /opt/python/*/bin; do
    OLDPIP=$("${PYBIN}/pip" freeze --all | grep '^pip==' | tr -d '\n')
    OLDWHEEL=$("${PYBIN}/pip" freeze --all | grep '^wheel==' | tr -d '\n')
    "${PYBIN}/pip" install -U pip wheel --no-warn-script-location
    "${PYBIN}/pip" install -r build-requirements.txt
    "${PYBIN}/pip" wheel . -v -w wheelhouse/ --no-deps
    "${PYBIN}/pip" install --force "$OLDPIP" "$OLDWHEEL"
done

# Bundle external shared libraries into the wheels
for whl in wheelhouse/*.whl; do
    auditwheel repair "$whl" -w dist
done

# Install and test
cd test
for PYBIN in /opt/python/*/bin/; do
    "${PYBIN}/pip" install -r ../test-requirements.txt
    "${PYBIN}/pip" install simplejpeg --no-index -f ../dist
    "${PYBIN}/python" -m pytest -vv
done
cd ..
