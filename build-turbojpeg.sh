#!/bin/bash
set -e -x

# install cmake and YASM to compile SIMD assembly
yum update -y
yum install -y cmake yasm

# checkout specific libjpeg-turbo tag from github
mkdir -p lib
cd lib
if [[ ! -e libjpeg-turbo ]]; then
    git clone --branch 2.0.4 --depth 1 https://github.com/libjpeg-turbo/libjpeg-turbo.git
fi

# build libjpeg-turbo
cd libjpeg-turbo
mkdir -p build
cd build
cmake -G"Unix Makefiles" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=. \
    -DENABLE_SHARED=0 \
    -DREQUIRE_SIMD=1 \
    -DCMAKE_C_FLAGS="-fPIC" \
    ..
make
