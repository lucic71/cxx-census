#!/bin/bash -eu

cmake -S "$SRC/nebula" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DENABLE_TESTING=OFF -DENABLE_WERROR=OFF -DENABLE_CCACHE=OFF
cmake --build "$BUILD" -j "$(nproc)"
