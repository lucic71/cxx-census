#!/bin/bash -eu

cmake -S "$SRC/yoga" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_PROJECT_INCLUDE=/census/projects/yoga/no-exceptions.cmake
cmake --build "$BUILD" -j "$(nproc)"
