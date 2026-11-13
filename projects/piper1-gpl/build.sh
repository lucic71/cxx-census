#!/bin/bash -eu

export CXX="$CXX $CXXFLAGS" CC="$CC $CFLAGS"
cmake -S "$SRC/piper1-gpl/libpiper" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$BUILD" -j "$(nproc)"
