#!/bin/bash
set -e -x

PYBIN=/opt/python/cp39-cp39/bin
"${PYBIN}/python" check_artifacts.py dist \
    --python-versions cp36 cp37 cp38 cp39 cp310 \
    --platforms macosx_10_9_x86_64 \
                manylinux1_i686 \
                manylinux1_x86_64 \
                manylinux_2_5_i686 \
                manylinux_2_5_x86_64 \
                manylinux_2_12_i686 \
                manylinux_2_12_x86_64 \
                manylinux_2_17_aarch64 \
                manylinux_2_17_i686 \
                manylinux_2_17_x86_64 \
                manylinux_2_24_aarch64 \
                manylinux_2_24_i686 \
                manylinux_2_24_x86_64 \
                manylinux2010_i686 \
                manylinux2010_x86_64 \
                manylinux2014_aarch64 \
                manylinux2014_i686 \
                manylinux2014_x86_64 \
                win32 \
                win_amd64 \
    --exclude cp310-manylinux1_i686 \
              cp310-manylinux1_x86_64 \
              cp310-manylinux_2_5_i686 \
              cp310-manylinux_2_5_x86_64 \
              cp310-manylinux_2_12_i686 \
              cp310-manylinux_2_12_x86_64 \
              cp310-manylinux_2_12_i686 \
              cp310-manylinux_2_12_x86_64 \
              cp310-manylinux_2_17_i686 \
              cp310-manylinux_2_24_i686 \
              cp310-manylinux2010_i686 \
              cp310-manylinux2010_x86_64 \
              cp310-manylinux2014_i686
