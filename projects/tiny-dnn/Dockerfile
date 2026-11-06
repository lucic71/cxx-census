FROM census-base

RUN git init $SRC/tiny-dnn \
    && git -C $SRC/tiny-dnn remote add origin https://github.com/tiny-dnn/tiny-dnn.git \
    && git -C $SRC/tiny-dnn fetch --depth 1 origin c0f576f5cb7b35893f62127cb7aec18f77a3bcc5 \
    && git -C $SRC/tiny-dnn checkout FETCH_HEAD
