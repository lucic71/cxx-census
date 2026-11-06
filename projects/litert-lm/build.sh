#!/bin/bash -eu

cd "$SRC/litert-lm"
opts=()
for f in $CXXFLAGS; do opts+=("--cxxopt=$f" "--host_cxxopt=$f"); done
bazel --output_user_root="$BUILD" build --config=linux_x86_64 --subcommands --jobs="$(nproc)" \
  --repo_env=CC="$CC" --repo_env=CXX="$CXX" --action_env=CC="$CC" --action_env=CXX="$CXX" \
  --java_runtime_version=remotejdk_17 "${opts[@]}" //runtime/engine:litert_lm_main
