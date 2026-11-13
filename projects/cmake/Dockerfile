FROM census-base

RUN git init $SRC/cmake \
    && git -C $SRC/cmake remote add origin https://github.com/Kitware/CMake.git \
    && git -C $SRC/cmake fetch --depth 1 origin 98dacb781776eea7165ba735d9fb5d51bbf04075 \
    && git -C $SRC/cmake checkout FETCH_HEAD
