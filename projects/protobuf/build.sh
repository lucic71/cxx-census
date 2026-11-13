#!/bin/bash -eu

cmake -S "$SRC/protobuf" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -Dprotobuf_BUILD_TESTS=OFF -Dprotobuf_ABSL_PROVIDER=module -Dprotobuf_BUILD_CONFORMANCE=OFF
cmake --build "$BUILD" -j "$(nproc)"
