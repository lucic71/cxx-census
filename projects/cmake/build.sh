#!/bin/bash -eu

cmake -S "$SRC/cmake" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_USE_OPENSSL=OFF -DBUILD_TESTING=OFF -DBUILD_CursesDialog=OFF -DBUILD_QtDialog=OFF
cmake --build "$BUILD" -j "$(nproc)"
