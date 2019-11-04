#!/bin/bash
set -e -x

PYBIN=/opt/python/cp37
${PYBIN}/pip" install twine
twine upload dist/*
