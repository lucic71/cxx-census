FROM census-base

RUN git init $SRC/bullet3 \
    && git -C $SRC/bullet3 remote add origin https://github.com/bulletphysics/bullet3.git \
    && git -C $SRC/bullet3 fetch --depth 1 origin d3afe76132fc76b0f9b2359cbaef47a3766e7fbb \
    && git -C $SRC/bullet3 checkout FETCH_HEAD
