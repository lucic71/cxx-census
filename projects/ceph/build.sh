#!/bin/bash -eu

mkdir -p "$BUILD"
cd "$SRC/boost_1_87_0"
./tools/build/src/engine/build.sh --cxx="$CXX" clang
printf 'using clang : : %s ;\nusing python : 3.12 ;\n' "$CXX" > "$BUILD/user-config.jam"
boost() {
  rm -rf "$BUILD/boost"
  ./tools/build/src/engine/b2 -j"$(nproc)" -d+2 --user-config="$BUILD/user-config.jam" --build-dir="$BUILD/boost" \
    --prefix="$BUILD/deps" --without-mpi --without-graph_parallel toolset=clang variant=release link=shared \
    threading=multi cxxflags="-fPIC $1" install
}
boost "${CXXFLAGS:-}" || { boost ""; echo "census: dep boost built without plugin"; }
cmake -S "$SRC/ceph" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DWITH_PYTHON3=3.12 \
  -DWITH_SYSTEM_BOOST=ON -DBOOST_ROOT="$BUILD/deps" -DWITH_MGR_DASHBOARD_FRONTEND=OFF \
  -DWITH_RADOSGW_LANCEDB=OFF -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$BUILD" -j "$(nproc)"
