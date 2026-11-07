#!/bin/bash -eu

cmake -S "$SRC/shadps4" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_CXX_FLAGS="$CXXFLAGS -fno-builtin-std-forward_like" \
  -DCMAKE_C_COMPILE_OBJECT="<CMAKE_C_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -march=native -o <OBJECT> -c <SOURCE>" \
  -DCMAKE_CXX_COMPILE_OBJECT="<CMAKE_CXX_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -march=native -o <OBJECT> -c <SOURCE>"
cmake --build "$BUILD" -j "$(nproc)"
