#!/bin/bash -eu

deps() { conan install "$SRC/rippled" --output-folder "$BUILD/deps" --build '*' -s:a build_type=Release -o '&:xrpld=True' "$@"; }
deps -c:a tools.build:cxxflags="['$CXXFLAGS']" || {
  conan remove '*' -c; rm -rf "$BUILD/deps"
  (unset CXXFLAGS; deps)
  echo "census: dep conan-deps built without plugin"
}
cmake -S "$SRC/rippled" -B "$BUILD/rippled" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_TOOLCHAIN_FILE="$BUILD/deps/build/generators/conan_toolchain.cmake" -Dxrpld=ON
cmake --build "$BUILD/rippled" -j "$(nproc)"
