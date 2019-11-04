#!/bin/bash
set -e -x

PYBIN=/opt/python/cp37-cp37m/bin
"${PYBIN}/pip" install twine
"${PYBIN}/python" -m twine upload --skip-existing --disable-progress-bar dist/*
