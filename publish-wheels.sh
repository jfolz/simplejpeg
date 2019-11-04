#!/bin/bash
set -e -x

PYBIN=/opt/python/cp37
"${PYBIN}/pip" install twine
twine upload --skip-existing --disable-progress-bar dist/*
