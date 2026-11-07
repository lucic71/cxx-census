FROM census-base

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      libjemalloc-dev libssl-dev zlib1g-dev liblz4-dev python3 python3-venv curl bzip2 \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/foundationdb \
    && git -C $SRC/foundationdb remote add origin https://github.com/apple/foundationdb.git \
    && git -C $SRC/foundationdb fetch --depth 1 origin a77f7f16b302f9ec1a774d23dfbe559b449eef3f \
    && git -C $SRC/foundationdb checkout FETCH_HEAD

RUN curl -fsSL https://archives.boost.io/release/1.89.0/source/boost_1_89_0.tar.bz2 | tar -xj -C $SRC

RUN python3 -m venv /opt/cmake && /opt/cmake/bin/pip install --no-cache-dir cmake==3.31.10
