#!/bin/bash -eu

export PKG_CONFIG_LIBDIR=/usr/lib/i386-linux-gnu/pkgconfig
cmake -S "$SRC/millennium" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_C_FLAGS="-m32 $CFLAGS" -DCMAKE_CXX_FLAGS="-m32 $CXXFLAGS" -DGITHUB_ACTION_BUILD=ON \
  -DCMAKE_LIBRARY_PATH=/usr/lib/i386-linux-gnu -DCMAKE_PREFIX_PATH=/usr/lib/i386-linux-gnu \
  -DCMAKE_SYSTEM_LIBRARY_PATH=/usr/lib/i386-linux-gnu -DPKG_CONFIG_USE_CMAKE_PREFIX_PATH=ON
cmake --build "$BUILD" -j "$(nproc)"
