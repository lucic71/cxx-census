#!/bin/bash -eu

cd "$SRC/perfetto"
tools/gn gen "$BUILD" --args="is_debug=false is_hermetic_clang=false enable_perfetto_x64_cpu_opt=false extra_cflags=\"$CFLAGS\""
tools/ninja -C "$BUILD" -v -j "$(nproc)"
