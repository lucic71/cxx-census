#!/bin/bash -eu

dep() {
  local n=$1; shift
  local a=(-S "$SRC/$n" -B "$BUILD/$n" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$BUILD/deps" -DCMAKE_PREFIX_PATH="$BUILD/deps" -DCMAKE_POSITION_INDEPENDENT_CODE=ON "$@")
  if ! { cmake "${a[@]}" -DCMAKE_CXX_FLAGS="$CXXFLAGS" && cmake --build "$BUILD/$n" -j "$(nproc)"; }; then
    rm -rf "$BUILD/$n"; echo "census: dep $n built without plugin"
    env -u CXXFLAGS cmake "${a[@]}" && env -u CXXFLAGS cmake --build "$BUILD/$n" -j "$(nproc)"
  fi
  cmake --install "$BUILD/$n"
}
dep fmt -DFMT_TEST=OFF -DFMT_DOC=OFF
dep spdlog -DSPDLOG_FMT_EXTERNAL=ON -DSPDLOG_BUILD_EXAMPLE=OFF -DSPDLOG_BUILD_SHARED=ON
dep expected -DEXPECTED_BUILD_TESTS=OFF
dep reproc -DREPROC++=ON -DBUILD_SHARED_LIBS=ON
dep msgpack-c -DMSGPACK_BUILD_TESTS=OFF -DMSGPACK_BUILD_EXAMPLES=OFF
dep libsolv -DENABLE_CONDA=ON -DMULTI_SEMANTICS=ON
dep simdjson -DSIMDJSON_DEVELOPER_MODE=OFF -DBUILD_SHARED_LIBS=ON
cmake -S "$SRC/mamba" -B "$BUILD/mamba" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_CXX_FLAGS="$CXXFLAGS -DSPDLOG_FMT_EXTERNAL" \
  -DCMAKE_PREFIX_PATH="$BUILD/deps" -DBUILD_LIBMAMBA=ON -DBUILD_LIBMAMBA_SPDLOG=ON -DBUILD_SHARED=ON -DBUILD_MAMBA=ON -DBUILD_MAMBA_PACKAGE=ON
cmake --build "$BUILD/mamba" -j "$(nproc)"
