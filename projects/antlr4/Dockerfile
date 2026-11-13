FROM census-base

RUN git init $SRC/antlr4 \
    && git -C $SRC/antlr4 remote add origin https://github.com/antlr/antlr4.git \
    && git -C $SRC/antlr4 fetch --depth 1 origin 45be27daf036f79eced0e3e215fdfee78b4b38d2 \
    && git -C $SRC/antlr4 checkout FETCH_HEAD
