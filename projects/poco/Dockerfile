FROM census-base

RUN git init $SRC/poco \
    && git -C $SRC/poco remote add origin https://github.com/pocoproject/poco.git \
    && git -C $SRC/poco fetch --depth 1 origin d2be2ecb1363b7d027b39c85dc190194f6527489 \
    && git -C $SRC/poco checkout FETCH_HEAD
