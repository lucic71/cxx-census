#!/bin/bash -eu

cmake -S "$SRC/flatbuffers" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_CXX_FLAGS="$CXXFLAGS -fno-exceptions" -DFLATBUFFERS_BUILD_TESTS=ON -DFLATBUFFERS_BUILD_FLATHASH=OFF
cmake --build "$BUILD" -j "$(nproc)"
