FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends llvm-18-dev liblld-18-dev zlib1g-dev libzstd-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/wasmedge \
    && git -C $SRC/wasmedge remote add origin https://github.com/WasmEdge/WasmEdge.git \
    && git -C $SRC/wasmedge fetch --depth 1 origin 617d724e2a1028721982804f22194942abe2e2a4 \
    && git -C $SRC/wasmedge checkout FETCH_HEAD
