#!/bin/bash -eu

cmake -S "$SRC/flashlight" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DFL_ARRAYFIRE_USE_CPU=ON
cmake --build "$BUILD" -j "$(nproc)"
