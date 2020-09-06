#!/bin/bash
set -e -x

PYBIN=/opt/python/cp38-cp38/bin
"${PYBIN}/pip" install -U cmake
cp "${PYBIN}/cmake" /usr/local/bin/
