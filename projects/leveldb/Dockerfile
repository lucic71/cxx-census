FROM census-base

RUN git clone https://github.com/google/leveldb.git $SRC/leveldb \
    && git -C $SRC/leveldb checkout bb74ef739973a70ca9f0d90788a1da89b788c0ad \
    && git -C $SRC/leveldb submodule update --init --depth 1 third_party/googletest
