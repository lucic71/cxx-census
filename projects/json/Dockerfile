FROM census-base

RUN git init $SRC/json \
    && git -C $SRC/json remote add origin https://github.com/nlohmann/json.git \
    && git -C $SRC/json fetch --depth 1 origin b54267d2a74c085ff2b05b01e369ecb7dd70cec6 \
    && git -C $SRC/json checkout FETCH_HEAD
