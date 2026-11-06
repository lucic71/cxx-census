FROM census-base

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends libjemalloc-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/ton \
    && git -C $SRC/ton remote add origin https://github.com/ton-blockchain/ton.git \
    && git -C $SRC/ton fetch --depth 1 origin 857b8a57a178e6ae0fe7fa86e7d81c5233de8560 \
    && git -C $SRC/ton checkout FETCH_HEAD \
    && git -C $SRC/ton submodule update --init --recursive --depth 1
