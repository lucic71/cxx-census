#!/bin/bash -eu

export PATH=/opt/cmake/bin:$PATH
mkdir -p "$BUILD"
cd "$SRC/boost_1_89_0"
./tools/build/src/engine/build.sh --cxx="$CXX" clang
echo "using clang : : $CXX ;" > "$BUILD/user-config.jam"
boost() {
  rm -rf "$BUILD/boost"
  ./tools/build/src/engine/b2 -j"$(nproc)" -d+2 --user-config="$BUILD/user-config.jam" --build-dir="$BUILD/boost" \
    --prefix="$BUILD/deps" --with-context --with-filesystem --with-iostreams --with-serialization \
    --with-program_options --with-url toolset=clang variant=release link=static -s NO_BZIP2=1 -s NO_LZMA=1 \
    -s NO_ZSTD=1 --disable-icu cxxflags="-fvisibility=hidden -fPIC -std=c++17 $1" install
}
boost "${CXXFLAGS:-}" || { boost ""; echo "census: dep boost built without plugin"; }
cmake -S "$SRC/foundationdb" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DUSE_LIBCXX=OFF \
  -DBOOST_ROOT="$BUILD/deps" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$BUILD" -j "$(nproc)"
