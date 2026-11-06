FROM census-base

RUN git init $SRC/rttr \
    && git -C $SRC/rttr remote add origin https://github.com/rttrorg/rttr.git \
    && git -C $SRC/rttr fetch --depth 1 origin 7edbd580cfad509a3253c733e70144e36f02ecd4 \
    && git -C $SRC/rttr checkout FETCH_HEAD
