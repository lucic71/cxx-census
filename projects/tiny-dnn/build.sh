#!/bin/bash -eu

cmake -S "$SRC/tiny-dnn" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_EXAMPLES=ON \
  -DCMAKE_CXX_FLAGS="$CXXFLAGS -Wno-missing-template-arg-list-after-template-kw"
cmake --build "$BUILD" -j "$(nproc)"
