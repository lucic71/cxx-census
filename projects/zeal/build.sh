#!/bin/bash -eu

cmake -S "$SRC/zeal" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  --compile-no-warning-as-error
cmake --build "$BUILD" -j "$(nproc)"
