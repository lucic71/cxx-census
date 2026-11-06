#!/bin/bash -eu

export LC_ALL=C.UTF-8
cmake -S "$SRC/kvrocks" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXE_LINKER_FLAGS=-latomic \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$BUILD" -j "$(nproc)"
