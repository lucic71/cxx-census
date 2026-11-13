#!/bin/bash -eu

mkdir -p "$BUILD"
cd "$SRC/litert-lm"
opts=()
for f in $CXXFLAGS; do opts+=("--cxxopt=$f" "--host_cxxopt=$f"); done
for f in $CFLAGS; do opts+=("--conlyopt=$f" "--host_conlyopt=$f"); done
bazel --output_user_root="$BUILD/bazel" build --config=linux_x86_64 --subcommands --keep_going --jobs="$(nproc)" \
  --repo_env=CC="$CC" --repo_env=CXX="$CXX" --action_env=CC="$CC" --action_env=CXX="$CXX" \
  --java_runtime_version=remotejdk_17 --copt=-DHWY_COMPILE_ONLY_STATIC=1 \
  --host_copt=-DHWY_COMPILE_ONLY_STATIC=1 "${opts[@]}" //runtime/engine:litert_lm_main
