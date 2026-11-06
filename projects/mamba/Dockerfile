FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      zlib1g-dev libarchive-dev libcurl4-openssl-dev libssl-dev libzstd-dev libbz2-dev \
      libyaml-cpp-dev nlohmann-json3-dev libcli11-dev libstdc++-14-dev python3 \
    && rm -rf /var/lib/apt/lists/*

RUN git clone --depth 1 -b 12.1.0 https://github.com/fmtlib/fmt.git $SRC/fmt \
    && git clone --depth 1 -b v1.16.0 https://github.com/gabime/spdlog.git $SRC/spdlog \
    && git clone --depth 1 -b v1.1.0 https://github.com/TartanLlama/expected.git $SRC/expected \
    && git clone --depth 1 -b v14.2.5 https://github.com/DaanDeMeyer/reproc.git $SRC/reproc \
    && git clone --depth 1 -b c-6.1.0 https://github.com/msgpack/msgpack-c.git $SRC/msgpack-c \
    && git clone --depth 1 -b 0.7.35 https://github.com/openSUSE/libsolv.git $SRC/libsolv \
    && git clone --depth 1 -b v4.6.11 https://github.com/simdjson/simdjson.git $SRC/simdjson

RUN git init $SRC/mamba \
    && git -C $SRC/mamba remote add origin https://github.com/mamba-org/mamba.git \
    && git -C $SRC/mamba fetch --depth 1 origin dfb70d06755116c155ae844b9701871efb19f662 \
    && git -C $SRC/mamba checkout FETCH_HEAD
