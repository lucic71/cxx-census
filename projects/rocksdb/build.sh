#!/bin/bash -eu

cmake -S "$SRC/rocksdb" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DFAIL_ON_WARNINGS=OFF -DWITH_SNAPPY=ON -DWITH_LZ4=ON -DWITH_ZLIB=ON -DWITH_ZSTD=ON -DWITH_BZ2=ON
cmake --build "$BUILD" -j "$(nproc)"
