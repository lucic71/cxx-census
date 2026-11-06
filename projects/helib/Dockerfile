FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends libntl-dev libgmp-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/helib \
    && git -C $SRC/helib remote add origin https://github.com/homenc/HElib.git \
    && git -C $SRC/helib fetch --depth 1 origin 3e337a66a91a92d49de6a9505340826b0eb71081 \
    && git -C $SRC/helib checkout FETCH_HEAD
