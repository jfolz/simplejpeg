CALL %1
cd libjpeg-turbo
mkdir -Force build
cd build
cmake -G"NMake Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=. -DENABLE_SHARED=0 -DREQUIRE_SIMD=1 ..
nmake
