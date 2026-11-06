FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends software-properties-common gpg-agent \
    && add-apt-repository -y ppa:ubuntu-toolchain-r/test \
    && apt-get update && apt-get install -y --no-install-recommends \
      libstdc++-16-dev lld-23 curl patch default-jre-headless python3 python3-pyelftools python3-pyparsing python3-jinja2 \
      libboost-dev libboost-filesystem-dev libboost-program-options-dev libboost-system-dev libboost-thread-dev \
      libboost-regex-dev libboost-test-dev libcrypto++-dev libgnutls28-dev libhwloc-dev liblz4-dev libnuma-dev \
      libpciaccess-dev libprotobuf-dev protobuf-compiler libsctp-dev libssl-dev liburing-dev libxml2-dev \
      libyaml-cpp-dev ragel libudev-dev libunistring-dev libzstd-dev systemtap-sdt-dev valgrind liblua5.3-dev \
      libsnappy-dev libjsoncpp-dev rapidjson-dev libdeflate-dev librapidxml-dev libxxhash-dev zlib1g-dev \
      libsystemd-dev libicu-dev libcrypt-dev libp11-kit-dev libldap-dev libcpp-jwt-dev \
    && rm -rf /var/lib/apt/lists/*

ENV PATH=/root/.cargo/bin:$PATH
RUN curl -sSf https://sh.rustup.rs | sh -s -- -y --profile minimal \
    && cargo install cxxbridge-cmd --version 1.0.83 --root /usr/local -j 8

RUN git init $SRC/scylladb \
    && git -C $SRC/scylladb remote add origin https://github.com/scylladb/scylladb.git \
    && git -C $SRC/scylladb fetch --depth 1 origin 6294ac2a14f0e7dca394d674584cb3e95b6d755c \
    && git -C $SRC/scylladb checkout FETCH_HEAD \
    && git -C $SRC/scylladb submodule update --init --recursive --depth 1 \
    && cd $SRC/scylladb && ./scripts/install-antlr3.sh
