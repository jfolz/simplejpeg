#!/bin/bash
set -e -x

PYBIN=/opt/python/cp39-cp39/bin
"${PYBIN}/python" check_artifacts.py \
    dist \
    --python-versions cp36 cp37 cp38 cp39 \
    --platforms manylinux1_x86_64 \
                manylinux1_i686 \
                manylinux2010_x86_64 \
                manylinux2010_i686 \
                manylinux2014_x86_64 \
                manylinux2014_i686 \
                win_amd64 win32 \
                macosx_10_9_x86_64
