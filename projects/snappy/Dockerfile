FROM census-base

RUN git clone https://github.com/google/snappy.git $SRC/snappy \
    && git -C $SRC/snappy checkout 946606459314e55d029c85f9a8c46f8809467f0f \
    && git -C $SRC/snappy submodule update --init --depth 1 third_party/googletest
