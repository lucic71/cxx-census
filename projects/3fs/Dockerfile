FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      lld-23 clang-format-14 meson google-perftools libaio-dev libboost-all-dev libdouble-conversion-dev libdwarf-dev \
      libgflags-dev libgmock-dev libgoogle-glog-dev libgoogle-perftools-dev libgtest-dev liblz4-dev liblzma-dev \
      libssl-dev libunwind-dev libuv1-dev libclang-rt-23-dev python3 rustc-1.91 cargo-1.91 \
    && rm -rf /var/lib/apt/lists/*

RUN wget -q https://github.com/apple/foundationdb/releases/download/7.3.63/foundationdb-clients_7.3.63-1_amd64.deb \
    && dpkg -i foundationdb-clients_7.3.63-1_amd64.deb && rm foundationdb-clients_7.3.63-1_amd64.deb

RUN wget -qO- https://github.com/libfuse/libfuse/releases/download/fuse-3.16.2/fuse-3.16.2.tar.gz | tar -xz -C /opt

ENV PATH=/usr/lib/rust-1.91/bin:/usr/lib/llvm-23/bin:$PATH

RUN git init $SRC/3fs \
    && git -C $SRC/3fs remote add origin https://github.com/deepseek-ai/3FS.git \
    && git -C $SRC/3fs fetch --depth 1 origin 22fca04564c7cc230fd8b9523b8b92864e1dad47 \
    && git -C $SRC/3fs checkout FETCH_HEAD \
    && git -C $SRC/3fs submodule update --init --recursive --depth 1 \
    && $SRC/3fs/patches/apply.sh
