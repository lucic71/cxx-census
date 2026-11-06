#!/bin/bash -eu

mbedtls() {
  rm -rf "$BUILD/mbedtls"
  cmake -S /opt/mbedtls-3.6.4 -B "$BUILD/mbedtls" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$BUILD/deps" \
    -DENABLE_TESTING=OFF -DENABLE_PROGRAMS=OFF -DCMAKE_POSITION_INDEPENDENT_CODE=ON
  cmake --build "$BUILD/mbedtls" -j "$(nproc)" && cmake --install "$BUILD/mbedtls"
}
mbedtls || { echo "census: dep mbedtls built without plugin"; CXXFLAGS= mbedtls; }

cmake -S "$SRC/imhex" -B "$BUILD/imhex" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="$BUILD/deps" -DIMHEX_STRICT_WARNINGS=OFF
cmake --build "$BUILD/imhex" -j "$(nproc)"
