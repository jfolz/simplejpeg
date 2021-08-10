#!/bin/bash
set -e -x
shopt -s extglob

echo "Available Python versions:"
ls -lh /opt/python/

echo "Selected Python versions:"
echo ${PYVERS}

echo "Matching Python versions:"
echo /opt/python/@(${PYVERS})*/bin

# Compile wheels
for PYBIN in /opt/python/@(${PYVERS})*/bin; do
    "${PYBIN}/pip" install -U pip --no-warn-script-location
    "${PYBIN}/pip" install -q build
    "${PYBIN}/python" -m build --wheel --outdir wheelhouse
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
