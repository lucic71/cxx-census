#!/bin/bash -eu

mkdir -p "$BUILD"
printf '#!/bin/bash\na=()\nfor x; do case "$x" in -fvar-tracking-assignments|-Werror|-Werror=*) ;; *) a+=("$x");; esac; done\nexec "${a[@]}"\n' > "$BUILD/wrap"
chmod +x "$BUILD/wrap"
L="CMAKE_C_COMPILER_LAUNCHER CMAKE_CXX_COMPILER_LAUNCHER CMAKE_C_LINKER_LAUNCHER CMAKE_CXX_LINKER_LAUNCHER"
export CXXFLAGS="${CXXFLAGS:-} -isystem $SRC/tendis/src/thirdparty/jemalloc/include"
cmake -S "$SRC/tendis" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_COMPILER_IS_GNUCC=ON \
  $(printf -- "-D%s=$BUILD/wrap " $L) -DCMAKE_TRY_COMPILE_PLATFORM_VARIABLES="${L// /;}"
cmake --build "$BUILD" -j "$(nproc)"
