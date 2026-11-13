#!/bin/bash -eu
# Needs the kernel tree mounted at $SRC/linux, e.g.
#   docker run --rm -v $CENSUS:/census -v /path/to/linux:/src/linux:ro \
#     -e CFLAGS="-fplugin=/census/build/plugin/census.so" census-linux /census/projects/linux/build.sh
# KCONFIG selects the config target (default: defconfig).

KCONFIG=${KCONFIG:-defconfig}
MAKE=(make -C "$SRC/linux" O="$BUILD" CC="$CC" HOSTCC="$CC" -j "$(nproc)" -k)

"${MAKE[@]}" "$KCONFIG"
# The census plugin only reads the AST; keep warnings from failing the build.
"$SRC/linux/scripts/config" --file "$BUILD/.config" -d WERROR
"${MAKE[@]}" olddefconfig
"${MAKE[@]}" KCFLAGS="$CFLAGS" vmlinux modules
