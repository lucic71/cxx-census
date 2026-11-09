#!/bin/bash -eu

git init "$SRC/clickhouse"
git -C "$SRC/clickhouse" remote add origin https://github.com/ClickHouse/ClickHouse.git
git -C "$SRC/clickhouse" fetch --depth 1 origin b7920049a2e9c58a3c383da71cb0d8a835a65dd6
git -C "$SRC/clickhouse" checkout FETCH_HEAD
git -C "$SRC/clickhouse" submodule update --init --recursive --depth 1 --jobs 16
CXXFLAGS= cmake -S "$SRC/clickhouse" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_CXX_FLAGS_RELEASE="-O3 -DNDEBUG $CXXFLAGS" -DCOMPILER_CACHE=disabled -DX86_ARCH_LEVEL=1 -DENABLE_RUST=OFF
cmake --build "$BUILD" -j "$(nproc)"
