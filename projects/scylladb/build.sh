#!/bin/bash -eu

make -C "$SRC/lz4/lib" -j "$(nproc)" CC="$CC" PREFIX="$BUILD/deps" install
cd "$SRC/scylladb"
./configure.py --mode=release --build-dir="$BUILD" --compiler="$CXX" --c-compiler="$CC" \
  --cflags="$CXXFLAGS -I$BUILD/deps/include" --ldflags="-L$BUILD/deps/lib"
ninja -v -j 16 "$BUILD/release/scylla"
