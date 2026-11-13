FROM census-base

RUN git init $SRC/googletest \
    && git -C $SRC/googletest remote add origin https://github.com/google/googletest.git \
    && git -C $SRC/googletest fetch --depth 1 origin 845e54d32d86ee1bb872ebb5b1c755e6e3a94c34 \
    && git -C $SRC/googletest checkout FETCH_HEAD
