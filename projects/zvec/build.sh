#!/bin/bash -eu

mkdir -p "$BUILD"
printf '#!/bin/bash\n[[ " $* " == *" %s "* ]] && exec "$@"\nexec "$@" %s\n' "${CXXFLAGS:-}" "${CXXFLAGS:-}" > "$BUILD/cxx-launcher"
chmod +x "$BUILD/cxx-launcher"
cmake -S "$SRC/zvec" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DAUTO_DETECT_ARCH=OFF \
  -DCMAKE_C_COMPILER_LAUNCHER=env -DCMAKE_CXX_COMPILER_LAUNCHER="$BUILD/cxx-launcher"
cmake --build "$BUILD" -j "$(nproc)"
