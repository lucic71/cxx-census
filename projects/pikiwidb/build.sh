#!/bin/bash -eu

export CXXFLAGS="$CXXFLAGS -stdlib=libstdc++" LDFLAGS="-stdlib=libstdc++"
export CC="$CC -Wno-error=incompatible-pointer-types -Wno-error=implicit-function-declaration -Wno-error=int-conversion"
cmake -S "$SRC/pikiwidb" -B "$BUILD" -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$BUILD" -j "$(nproc)"
