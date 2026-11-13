FROM census-base

RUN git init $SRC/yaml-cpp \
    && git -C $SRC/yaml-cpp remote add origin https://github.com/jbeder/yaml-cpp.git \
    && git -C $SRC/yaml-cpp fetch --depth 1 origin f473f3bdfed25271ebd3d268caedc1b0b7f5ff50 \
    && git -C $SRC/yaml-cpp checkout FETCH_HEAD
