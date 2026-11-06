FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends libclang-rt-23-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/cxxopts \
    && git -C $SRC/cxxopts remote add origin https://github.com/jarro2783/cxxopts.git \
    && git -C $SRC/cxxopts fetch --depth 1 origin 7af8aad55eddd73715ded20d4478e242424a0bda \
    && git -C $SRC/cxxopts checkout FETCH_HEAD
