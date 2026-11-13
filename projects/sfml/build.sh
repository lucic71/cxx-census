#!/bin/bash -eu

cmake -S "$SRC/sfml" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DSFML_USE_SYSTEM_DEPS=ON -DSFML_BUILD_AUDIO=OFF
cmake --build "$BUILD" -j "$(nproc)"
