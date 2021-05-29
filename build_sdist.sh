#!/bin/bash
set -e -x

PYBIN="/opt/python/cp39-cp39/bin"
"${PYBIN}/pip" install -q build
"${PYBIN}/python" -m build --sdist
