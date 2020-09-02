#!/bin/bash
set -e -x

PYBIN=/opt/python/cp38-cp38/bin
"${PYBIN}/python" check_artifacts.py \
    dist \
    --python-versions cp35 cp36 cp37 cp38 \
    --platforms manylinux2010_x86_64 manylinux2010_i686 win_amd64 win32 macosx_10_9_x86_64
