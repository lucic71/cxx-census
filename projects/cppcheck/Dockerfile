FROM census-base

RUN git init $SRC/cppcheck \
    && git -C $SRC/cppcheck remote add origin https://github.com/cppcheck-opensource/cppcheck.git \
    && git -C $SRC/cppcheck fetch --depth 1 origin 8df3087f48aa70a2e0e54ec05324f7147ec3e0b6 \
    && git -C $SRC/cppcheck checkout FETCH_HEAD
