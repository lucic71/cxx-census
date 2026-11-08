#!/bin/bash -eu

cd "$SRC/memgraph"
mkdir -p "$BUILD" && ln -sfn "$BUILD" build
F=$(python3 -c 'import json,os,shlex; print(json.dumps(shlex.split(os.environ["CXXFLAGS"])))')
export CXXFLAGS_x86_64_unknown_linux_gnu="-stdlib=libc++ $CXXFLAGS" CXXSTDLIB=c++
unset CXXFLAGS
conan profile detect --force
conan config install conan_config
conan remote add memgraph-recipes "$PWD/conan_recipes" -t local-recipes-index --force
conan install . --build=missing -pr:h default -pr:h memgraph_linux_base -pr:b memgraph_build_profile \
  -s build_type=Release -s compiler.libcxx=libc++ -s os.distro=ubuntu-24.04 -o "&:bundled_toolchain=False" --lockfile-partial \
  -c:a tools.build:compiler_executables='{"c": "clang-23", "cpp": "clang++-23"}' -c:a tools.build:cxxflags="$F" \
  -c:a 'aws-sdk-cpp/*:tools.cmake.cmaketoolchain:extra_variables={"AWS_SDK_WARNINGS_ARE_ERRORS": "OFF"}' \
  -c:a 'fmt/*:tools.cmake.cmaketoolchain:extra_variables={"FMT_MODULE": "OFF"}'
source build/generators/conanbuild.sh
printf '#!/bin/bash\nfor a; do [[ $a == *.cpp ]] && exec "$@" -include ranges; done\nexec "$@"\n' > "$BUILD/launcher"
chmod +x "$BUILD/launcher"
cmake --preset conan-release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DMG_TOOLCHAIN_ROOT=/usr -DCCACHE_PROGRAM=OFF \
  -DCMAKE_CXX_COMPILER_LAUNCHER="$BUILD/launcher"
cmake --build --preset conan-release -j "$(nproc)"
