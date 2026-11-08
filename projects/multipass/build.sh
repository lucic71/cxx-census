#!/bin/bash -eu

CXXFLAGS="$CXXFLAGS -Wno-error=fortify-source" cmake -S "$SRC/multipass" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DMULTIPASS_ENABLE_FLUTTER_GUI=OFF
cmake --build "$BUILD" -j "$(nproc)"
