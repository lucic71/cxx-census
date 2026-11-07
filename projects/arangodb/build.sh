#!/bin/bash -eu

cmake -S "$SRC/arangodb" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DUSE_GOOGLE_TESTS=Off -DUSE_MAINTAINER_MODE=Off -DUSE_FAILURE_TESTS=Off -DUSE_FAIL_ON_WARNINGS=Off -DTARGET_ARCHITECTURE=native -DUSE_IPO=Off \
  -DCMAKE_EXE_LINKER_FLAGS=-fuse-ld=lld -DCMAKE_SHARED_LINKER_FLAGS=-fuse-ld=lld
cmake --build "$BUILD" -j "$(nproc)"
