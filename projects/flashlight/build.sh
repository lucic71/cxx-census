#!/bin/bash -eu

cmake -S "$SRC/flashlight" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DFL_USE_ARRAYFIRE=OFF \
  -DCMAKE_CXX_COMPILE_OBJECT="<CMAKE_CXX_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -std=gnu++20 -fdelayed-template-parsing -DFMT_HEADER_ONLY -o <OBJECT> -c <SOURCE>"
cmake --build "$BUILD" -j "$(nproc)"
