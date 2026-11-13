FROM census-base

RUN git init $SRC/libzmq \
    && git -C $SRC/libzmq remote add origin https://github.com/zeromq/libzmq.git \
    && git -C $SRC/libzmq fetch --depth 1 origin 46493370217ac135246617fa2f6ac819d8b61bfc \
    && git -C $SRC/libzmq checkout FETCH_HEAD
