#!/bin/bash -eu

cmake -S "$SRC/cpp-httplib" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DHTTPLIB_COMPILE=ON -DHTTPLIB_TEST=ON
cmake --build "$BUILD" -j "$(nproc)"
