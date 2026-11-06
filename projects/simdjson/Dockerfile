FROM census-base

RUN git init $SRC/simdjson \
    && git -C $SRC/simdjson remote add origin https://github.com/simdjson/simdjson.git \
    && git -C $SRC/simdjson fetch --depth 1 origin dfe02cfe3737b42e48b65e946682e897bd1bdf0a \
    && git -C $SRC/simdjson checkout FETCH_HEAD
