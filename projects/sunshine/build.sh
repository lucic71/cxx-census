#!/bin/bash -eu

cmake -S "$SRC/sunshine" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DBUILD_DOCS=OFF -DSUNSHINE_ENABLE_CUDA=OFF
cmake --build "$BUILD" -j "$(nproc)"
