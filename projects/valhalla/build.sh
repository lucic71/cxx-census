#!/bin/bash -eu

a=(-S "$SRC/prime_server" -B "$BUILD/prime_server" -DCMAKE_BUILD_TYPE=Release -DENABLE_WERROR=OFF -DCMAKE_INSTALL_PREFIX="$BUILD/deps")
if ! { cmake "${a[@]}" -DCMAKE_CXX_FLAGS="$CXXFLAGS" && cmake --build "$BUILD/prime_server" -j "$(nproc)"; }; then
  rm -rf "$BUILD/prime_server"; echo "census: dep prime_server built without plugin"
  env -u CXXFLAGS -u CFLAGS cmake "${a[@]}" && env -u CXXFLAGS -u CFLAGS cmake --build "$BUILD/prime_server" -j "$(nproc)"
fi
cmake --install "$BUILD/prime_server"
cmake -S "$SRC/valhalla" -B "$BUILD/valhalla" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_PREFIX_PATH="$BUILD/deps"
cmake --build "$BUILD/valhalla" -j "$(nproc)"
