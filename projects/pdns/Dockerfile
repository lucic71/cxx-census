FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      bison flex ragel curl python3 python3-yaml python3-venv meson libboost-all-dev libcdb-dev libcurl4-openssl-dev \
      liblmdb-dev libluajit-5.1-dev libprotobuf-dev protobuf-compiler libsodium-dev libsqlite3-dev libssl-dev \
      libsystemd-dev libyaml-cpp-dev libcap-dev libfstrm-dev libgnutls28-dev libsnmp-dev libedit-dev \
      libnghttp2-dev libre2-dev libbpf-dev libxdp-dev libwslay-dev libmaxminddb-dev \
    && rm -rf /var/lib/apt/lists/*

RUN curl -sSf https://sh.rustup.rs | sh -s -- -y --profile minimal --default-toolchain 1.93.0
ENV PATH=/root/.cargo/bin:$PATH

RUN git init $SRC/pdns \
    && git -C $SRC/pdns remote add origin https://github.com/PowerDNS/pdns.git \
    && git -C $SRC/pdns fetch --depth 1 origin 212cee57fe3291650efaa9277b42b43a5fefc508 \
    && git -C $SRC/pdns checkout FETCH_HEAD
