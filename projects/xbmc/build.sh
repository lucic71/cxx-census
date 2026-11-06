#!/bin/bash -eu

cmake -S "$SRC/xbmc" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DENABLE_INTERNAL_FFMPEG=ON -DENABLE_INTERNAL_SWIG=ON
cmake --build "$BUILD" -j "$(nproc)"
