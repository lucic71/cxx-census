FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libgflags-dev liburing-dev libsnappy-dev zlib1g-dev libbz2-dev liblz4-dev libzstd-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/rocksdb \
    && git -C $SRC/rocksdb remote add origin https://github.com/facebook/rocksdb.git \
    && git -C $SRC/rocksdb fetch --depth 1 origin 0e768876e59ab624896909b4c6e1bb246f40d7c5 \
    && git -C $SRC/rocksdb checkout FETCH_HEAD
