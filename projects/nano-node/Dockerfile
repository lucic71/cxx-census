FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends python3 zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/nano-node \
    && git -C $SRC/nano-node remote add origin https://github.com/nanocurrency/nano-node.git \
    && git -C $SRC/nano-node fetch --depth 1 origin 4daa8b52af7dd15a581d6b0c2d1488e4479014c0 \
    && git -C $SRC/nano-node checkout FETCH_HEAD \
    && git -C $SRC/nano-node submodule update --init --recursive --depth 1 --jobs 16
