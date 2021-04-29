#!/bin/bash
set -e -x

# Python 2.7, 3.4, 3.5, and 3.6 are not supported
# remove binaries if still present
rm -rf /opt/python/cp27*
rm -rf /opt/python/cp34*
rm -rf /opt/python/cp35*
rm -rf /opt/python/cp36*

# Compile wheels
for PYBIN in /opt/python/*/bin; do
    "${PYBIN}/pip" install -U pip --no-warn-script-location
    "${PYBIN}/pip" install --only-binary ":all:" -r build_requirements.txt
    "${PYBIN}/pip" wheel . -v -w wheelhouse/ --no-deps --use-feature=in-tree-build
done

# Bundle external shared libraries into the wheels
for whl in wheelhouse/*.whl; do
    auditwheel repair "$whl" -w dist
done

# Install and test
cd test
for PYBIN in /opt/python/*/bin/; do
    "${PYBIN}/pip" install --only-binary ":all:" -r ../test_requirements.txt
    "${PYBIN}/pip" install simplejpeg --no-index -f ../dist
    "${PYBIN}/python" -m pytest -vv
done
cd ..
