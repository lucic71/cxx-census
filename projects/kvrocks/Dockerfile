FROM census-base

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends libtool autoconf automake python3 libssl-dev curl \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/kvrocks \
    && git -C $SRC/kvrocks remote add origin https://github.com/apache/kvrocks.git \
    && git -C $SRC/kvrocks fetch --depth 1 origin c256cc6e3168289727a8dfbbb518aad8c8dc0dc4 \
    && git -C $SRC/kvrocks checkout FETCH_HEAD
