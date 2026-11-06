#!/bin/bash -eu

fuse() { rm -rf "$BUILD/fuse" && meson setup "$BUILD/fuse" /opt/fuse-3.16.2 --prefix="$BUILD/deps" --libdir=lib \
  -Ddefault_library=both -Dutils=false -Dexamples=false -Dtests=false && ninja -C "$BUILD/fuse" install; }
fuse || { env -u CXXFLAGS bash -c "$(declare -f fuse); fuse" && echo "census: dep libfuse built without plugin"; }
export CPATH="$BUILD/deps/include" LIBRARY_PATH="$BUILD/deps/lib" LD_LIBRARY_PATH="$BUILD/deps/lib"
cmake -S "$SRC/3fs" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DSHUFFLE_METHOD=g++11 -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_CXX_COMPILER_LAUNCHER=no-coroutines-ts -DCMAKE_CXX_LINKER_LAUNCHER=no-coroutines-ts
cmake --build "$BUILD" -j "$(nproc)"
