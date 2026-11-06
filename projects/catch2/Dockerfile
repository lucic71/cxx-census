FROM census-base

RUN git init $SRC/catch2 \
    && git -C $SRC/catch2 remote add origin https://github.com/catchorg/Catch2.git \
    && git -C $SRC/catch2 fetch --depth 1 origin a1a991fee5f217b40035cb2f8ebc83864d66408d \
    && git -C $SRC/catch2 checkout FETCH_HEAD
