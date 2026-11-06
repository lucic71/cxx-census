FROM census-base

RUN git init $SRC/or-tools \
    && git -C $SRC/or-tools remote add origin https://github.com/google/or-tools.git \
    && git -C $SRC/or-tools fetch --depth 1 origin 100f66e6242ab8bf8d32feb8f3bf086db66ae2b5 \
    && git -C $SRC/or-tools checkout FETCH_HEAD
