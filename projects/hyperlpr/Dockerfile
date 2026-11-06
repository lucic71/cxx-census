FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends libopencv-dev libc++-23-dev libc++abi-23-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/hyperlpr \
    && git -C $SRC/hyperlpr remote add origin https://github.com/szad670401/HyperLPR.git \
    && git -C $SRC/hyperlpr fetch --depth 1 origin 9307450f7b7915be18f23a539ec05b41fe6629f4 \
    && git -C $SRC/hyperlpr checkout FETCH_HEAD
