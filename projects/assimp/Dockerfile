FROM census-base

RUN git init $SRC/assimp \
    && git -C $SRC/assimp remote add origin https://github.com/assimp/assimp.git \
    && git -C $SRC/assimp fetch --depth 1 origin 3f1e307a60b0d4f5d4ed22f879c52ace20739472 \
    && git -C $SRC/assimp checkout FETCH_HEAD
