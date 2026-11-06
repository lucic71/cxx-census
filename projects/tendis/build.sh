#!/bin/bash -eu

mkdir -p "$BUILD"
printf '#!/bin/bash\na=()\nfor x; do [ "$x" = -fvar-tracking-assignments ] || a+=("$x"); done\nexec "${a[@]}"\n' > "$BUILD/drop-flag"
chmod +x "$BUILD/drop-flag"
L="CMAKE_C_COMPILER_LAUNCHER CMAKE_CXX_COMPILER_LAUNCHER CMAKE_C_LINKER_LAUNCHER CMAKE_CXX_LINKER_LAUNCHER"
cmake -S "$SRC/tendis" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_COMPILER_IS_GNUCC=ON \
  -DCMAKE_CXX_FLAGS_RELEASE="-O3 -DNDEBUG -Wno-missing-format-attribute" \
  $(printf -- "-D%s=$BUILD/drop-flag " $L) -DCMAKE_TRY_COMPILE_PLATFORM_VARIABLES="${L// /;}"
cmake --build "$BUILD" -j "$(nproc)"
