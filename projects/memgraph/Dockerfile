FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      g++-14 libstdc++-14-dev lld-23 gperf libreadline-dev libpython3-dev python3-dev python3-venv python3-pip \
      python3-yaml patchelf libssl-dev autoconf libtool libkrb5-dev rustc-1.91 cargo-1.91 \
    && rm -rf /var/lib/apt/lists/*

RUN python3 -m venv /opt/conan && /opt/conan/bin/pip install "conan>=2.26.0"
ENV PATH=/opt/conan/bin:/usr/lib/rust-1.91/bin:/usr/lib/llvm-23/bin:$PATH

RUN git init $SRC/memgraph \
    && git -C $SRC/memgraph remote add origin https://github.com/memgraph/memgraph.git \
    && git -C $SRC/memgraph fetch --depth 1 origin 08d2ade3c96bc2e4905594873d391eb88db72ada \
    && git -C $SRC/memgraph checkout FETCH_HEAD
