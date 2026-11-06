FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      autoconf automake libtool libc++-23-dev libc++abi-23-dev lld-23 \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/pikiwidb \
    && git -C $SRC/pikiwidb remote add origin https://github.com/OpenAtomFoundation/pikiwidb.git \
    && git -C $SRC/pikiwidb fetch --depth 1 origin e5887a5bc3a4d60511b1304fe1dc506d053e6529 \
    && git -C $SRC/pikiwidb checkout FETCH_HEAD
