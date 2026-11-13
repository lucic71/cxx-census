#!/bin/bash -eu

cmake -S "$SRC/glog" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DWITH_GFLAGS=OFF -DWITH_GTEST=OFF -DBUILD_TESTING=OFF
cmake --build "$BUILD" -j "$(nproc)"
