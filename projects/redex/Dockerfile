FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      autoconf autoconf-archive automake binutils-dev libiberty-dev libjemalloc-dev libjsoncpp-dev \
      liblz4-dev liblzma-dev libtool python3 zlib1g-dev libprotobuf-dev protobuf-compiler \
      libboost-filesystem-dev libboost-iostreams-dev libboost-program-options-dev \
      libboost-regex-dev libboost-system-dev libboost-thread-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/redex \
    && git -C $SRC/redex remote add origin https://github.com/facebook/redex.git \
    && git -C $SRC/redex fetch --depth 1 origin 1486c67d867e7040b42e8eb37eab940881def4ca \
    && git -C $SRC/redex checkout FETCH_HEAD
