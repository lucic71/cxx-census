#!/bin/bash -eu

cmake -S "$SRC/opencv" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DBUILD_LIST=core,imgproc,imgcodecs,features2d,flann,calib3d,objdetect,video,photo,ml \
  -DBUILD_TESTS=OFF -DBUILD_PERF_TESTS=OFF -DBUILD_EXAMPLES=OFF -DBUILD_opencv_apps=OFF -DWITH_IPP=OFF \
  -DWITH_ITT=OFF -DWITH_OPENCL=OFF -DBUILD_JAVA=OFF -DBUILD_opencv_python3=OFF
cmake --build "$BUILD" -j "$(nproc)"
