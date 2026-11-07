#!/bin/bash -eu

cmake -S "$SRC/openmw" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DOPENMW_USE_SYSTEM_MYGUI=OFF
cmake --build "$BUILD" -j "$(nproc)"
