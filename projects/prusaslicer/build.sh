#!/bin/bash -eu

export LC_ALL=C.UTF-8
deps() {
  cmake -S "$SRC/prusaslicer/deps" -B "$BUILD/deps" -DCMAKE_BUILD_TYPE=Release -DDEP_MAX_THREADS="$(nproc)" -DPrusaSlicer_deps_PLATFORM_PACKAGES="GMP;MPFR" \
    -DCMAKE_CXX_FLAGS_RELEASE="-O3 -DNDEBUG $1" -DCMAKE_C_FLAGS_RELEASE="-O3 -DNDEBUG $2" && cmake --build "$BUILD/deps"
}
deps "$CXXFLAGS" "$CFLAGS" || { rm -rf "$BUILD/deps"; echo "census: dep prusaslicer-deps built without plugin"; (unset CXXFLAGS CFLAGS; deps "" ""); }
cmake -S "$SRC/prusaslicer" -B "$BUILD/prusaslicer" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_PREFIX_PATH="$BUILD/deps/destdir/usr/local"
cmake --build "$BUILD/prusaslicer" -j "$(nproc)"
