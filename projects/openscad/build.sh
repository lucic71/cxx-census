#!/bin/bash -eu

cmake -S "$SRC/openscad" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCGAL_DIR=/opt/CGAL-6.0.1/lib/cmake/CGAL
cmake --build "$BUILD" -j "$(nproc)"
