#!/bin/bash
set -e -x

PYBIN=/opt/python/cp39-cp39/bin
"${PYBIN}/pip" install twine
"${PYBIN}/python" -m twine upload \
    --skip-existing \
    --disable-progress-bar \
    -u "${TWINE_USERNAME}" \
    -p "${TWINE_PASSWORD}" \
    dist/*
