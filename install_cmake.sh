#!/bin/bash
set -e -x

PYBIN=/opt/python/cp39-cp39/bin
"${PYBIN}/pip" install -U cmake
cp "${PYBIN}/cmake" /usr/local/bin/
