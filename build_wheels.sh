#!/bin/bash
set -e -x
shopt -s extglob

# Compile wheels
for PYBIN in /opt/python/@(${PYVERS})*/bin; do
    "${PYBIN}/pip" install -U pip --no-warn-script-location
    "${PYBIN}/pip" install --only-binary ":all:" -r build_requirements.txt
    "${PYBIN}/pip" wheel . -v -w wheelhouse/ --no-deps --use-feature=in-tree-build
    "${PYBIN}/pip" uninstall -r build_requirements.txt
done

# Bundle external shared libraries into the wheels
for whl in wheelhouse/*.whl; do
    auditwheel repair "$whl" -w dist
done

# Install and test
cd test
for PYBIN in /opt/python/@(${PYVERS})*/bin/; do
    "${PYBIN}/pip" install --only-binary ":all:" -r ../test_requirements.txt
    "${PYBIN}/pip" install simplejpeg --no-index -f ../dist
    "${PYBIN}/python" -m pytest -vv
done
cd ..
