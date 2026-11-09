#!/bin/bash -eu

cmake -S "$SRC/astyle/AStyle" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_CXX_FLAGS="$CXXFLAGS -fno-exceptions"
cmake --build "$BUILD" -j "$(nproc)"
cd "$SRC/astyle"
$CXX $CXXFLAGS -std=c++17 -O2 -DASTYLE_LIB -IAStyle/src -IAStyleTest/src -o "$BUILD/AStyleTest" AStyleTest/src/*.cpp AStyle/src/ASBeautifier.cpp AStyle/src/ASEnhancer.cpp AStyle/src/ASFormatter.cpp AStyle/src/ASResource.cpp AStyle/src/astyle_main.cpp -lgtest -pthread
