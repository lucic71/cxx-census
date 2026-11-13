#!/bin/bash -eu

dep() {
  local n=$1; shift
  local a=(-S "$SRC/$n" -B "$BUILD/$n" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$BUILD/deps" -DCMAKE_PREFIX_PATH="$BUILD/deps" "$@")
  if ! { cmake "${a[@]}" -DCMAKE_CXX_FLAGS="$CXXFLAGS" && cmake --build "$BUILD/$n" -j "$(nproc)"; }; then
    rm -rf "$BUILD/$n"; echo "census: dep $n built without plugin"
    env -u CXXFLAGS -u CFLAGS cmake "${a[@]}" && env -u CXXFLAGS -u CFLAGS cmake --build "$BUILD/$n" -j "$(nproc)"
  fi
  cmake --install "$BUILD/$n"
}
dep SDL -DSDL_TESTS=OFF
dep SDL_image -DSDLIMAGE_SAMPLES=OFF
dep SDL_mixer -DSDLMIXER_TESTS=OFF -DSDLMIXER_EXAMPLES=OFF
CXXFLAGS="$CXXFLAGS -I$BUILD/deps/include" cmake -S "$SRC/wesnoth" -B "$BUILD/wesnoth" -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_PREFIX_PATH="$BUILD/deps"
cmake --build "$BUILD/wesnoth" -j "$(nproc)"
