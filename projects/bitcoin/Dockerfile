FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      python3 libboost-dev libsqlite3-dev libcapnp-dev capnproto libzmq3-dev systemtap-sdt-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/bitcoin \
    && git -C $SRC/bitcoin remote add origin https://github.com/bitcoin/bitcoin.git \
    && git -C $SRC/bitcoin fetch --depth 1 origin 411c971e75ba8ef16855a41dfe2d31d574ebf507 \
    && git -C $SRC/bitcoin checkout FETCH_HEAD
