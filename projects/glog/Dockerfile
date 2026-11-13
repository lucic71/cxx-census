FROM census-base

RUN git init $SRC/glog \
    && git -C $SRC/glog remote add origin https://github.com/google/glog.git \
    && git -C $SRC/glog fetch --depth 1 origin 53d58e4531c7c90f71ddab503d915e027432447a \
    && git -C $SRC/glog checkout FETCH_HEAD
