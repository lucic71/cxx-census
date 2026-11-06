FROM census-base

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends libboost-all-dev libc-ares-dev libcrypto++-dev libfmt-dev libgnutls28-dev libhwloc-dev liblz4-dev libnuma-dev libpciaccess-dev libprotobuf-dev libsctp-dev libssl-dev libtool liburing-dev libxml2-dev libyaml-cpp-dev meson openssl protobuf-compiler python3 python3-pyelftools python3-yaml ragel liblttng-ust-dev xfslibs-dev libudev-dev libunistring-dev libzstd-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/seastar \
    && git -C $SRC/seastar remote add origin https://github.com/scylladb/seastar.git \
    && git -C $SRC/seastar fetch --depth 1 origin 6a752c50208583cb122c1b7c0a405804a94805d2 \
    && git -C $SRC/seastar checkout FETCH_HEAD \
    && git -C $SRC/seastar submodule update --init --recursive --depth 1

RUN git clone --depth 1 -b 11.1.4 https://github.com/fmtlib/fmt.git $SRC/fmt
