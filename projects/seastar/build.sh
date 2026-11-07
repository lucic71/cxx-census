#!/bin/bash -eu

fmt() {
  rm -rf "$BUILD/fmt"
  CXXFLAGS="$1" cmake -S "$SRC/fmt" -B "$BUILD/fmt" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$BUILD/deps" \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DFMT_TEST=OFF -DFMT_DOC=OFF -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    && cmake --build "$BUILD/fmt" --target install -j "$(nproc)"
}
fmt "${CXXFLAGS:-}" || { fmt ""; echo "census: dep fmt built without plugin"; }
cmake -S "$SRC/seastar" -B "$BUILD/seastar" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="$BUILD/deps" \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_CXX_STANDARD=23 -DSeastar_DOCS=OFF
cmake --build "$BUILD/seastar" -j "$(nproc)"
