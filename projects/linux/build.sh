#!/bin/bash -eu

KCONFIG=${KCONFIG:-defconfig}
MAKE=(make -C "$SRC/linux" O="$BUILD" CC="$CC" HOSTCC="$CC" -j "${JOBS:-$(nproc)}" -k)

"${MAKE[@]}" "$KCONFIG"
"$SRC/linux/scripts/config" --file "$BUILD/.config" -d WERROR
"${MAKE[@]}" olddefconfig
"${MAKE[@]}" KCFLAGS="$CFLAGS" vmlinux modules
