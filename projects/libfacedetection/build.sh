#!/bin/bash -eu

cmake -S "$SRC/libfacedetection" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_CXX_FLAGS="$CXXFLAGS -fno-exceptions" -DENABLE_AVX2=OFF -DUSE_OPENMP=OFF -DDEMO=OFF
cmake --build "$BUILD" -j "$(nproc)"
