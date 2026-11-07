FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      bison flex python3-pip libarchive-dev libbrotli-dev libsodium-dev libzstd-dev libssl-dev \
      libsqlite3-dev nlohmann-json3-dev libseccomp-dev libgc-dev libtoml11-dev liblowdown-dev \
      libreadline-dev libcpuid-dev libnghttp2-dev libc++-23-dev libc++abi-23-dev \
      libpsl-dev zlib1g-dev libbz2-dev liblzma-dev libssh2-1-dev \
    && rm -rf /var/lib/apt/lists/* \
    && pip3 install --break-system-packages meson==1.9.1

RUN wget -qO- https://archives.boost.io/release/1.89.0/source/boost_1_89_0.tar.bz2 | tar xj -C $SRC \
    && git clone --depth 1 -b curl-8_17_0 https://github.com/curl/curl.git $SRC/curl \
    && git clone --depth 1 -b v1.9.1 https://github.com/libgit2/libgit2.git $SRC/libgit2 \
    && git clone --depth 1 -b 1.8.2 https://github.com/BLAKE3-team/BLAKE3.git $SRC/blake3

RUN git init $SRC/nix \
    && git -C $SRC/nix remote add origin https://github.com/NixOS/nix.git \
    && git -C $SRC/nix fetch --depth 1 origin 3ecf7b79088b6a0011d3a5ad58943dd27c368c8b \
    && git -C $SRC/nix checkout FETCH_HEAD
