#!/bin/bash -eu

cd "$SRC/plotjuggler"
deps() {
  conan install . --output-folder="$BUILD/conan" --build=missing -r=plotjuggler-conan -r=conancenter \
    --lockfile=conan.lock --lockfile-partial -s build_type=Release -s compiler.cppstd=20 "$@"
}
deps -c "tools.build:cxxflags=['$CXXFLAGS']" || { echo "census: dep conan packages built without plugin"; CXXFLAGS= deps; }

cmake -S . -B "$BUILD/pj" -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE="$BUILD/conan/conan_toolchain.cmake" -DCMAKE_PREFIX_PATH=/opt/Qt/6.12.0/gcc_64
cmake --build "$BUILD/pj" -j "$(nproc)"
