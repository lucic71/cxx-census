FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      python3 \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/llvm \
    && git -C $SRC/llvm remote add origin https://github.com/llvm/llvm-project.git \
    && git -C $SRC/llvm fetch --depth 1 origin 2451a1eadfa1636510e65c1688b006a0eedf20d8 \
    && git -C $SRC/llvm checkout FETCH_HEAD
