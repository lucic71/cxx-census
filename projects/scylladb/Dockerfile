FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends software-properties-common gpg-agent \
    && add-apt-repository -y ppa:ubuntu-toolchain-r/test \
    && apt-get update && apt-get install -y --no-install-recommends \
      libstdc++-16-dev lld-23 curl patch default-jre-headless python3 python3-pyelftools python3-pyparsing python3-jinja2 \
      libboost-dev libboost-filesystem-dev libboost-program-options-dev libboost-system-dev libboost-thread-dev \
      libboost-regex-dev libboost-test-dev libboost-container-dev libcrypto++-dev libgnutls28-dev libhwloc-dev liblz4-dev libnuma-dev \
      libpciaccess-dev libprotobuf-dev protobuf-compiler libsctp-dev libssl-dev liburing-dev libxml2-dev \
      libyaml-cpp-dev ragel libudev-dev libunistring-dev libzstd-dev systemtap-sdt-dev valgrind liblua5.3-dev \
      libsnappy-dev libjsoncpp-dev libdeflate-dev librapidxml-dev libxxhash-dev zlib1g-dev \
      libsystemd-dev libicu-dev libcrypt-dev libp11-kit-dev libldap-dev doxygen file python3-yaml xfslibs-dev \
    && rm -rf /var/lib/apt/lists/*

ENV PATH=/root/.cargo/bin:$PATH
RUN sed -i "s/^ID_LIKE=.*/ID_LIKE=\"debian fedora\"/" /usr/lib/os-release \
    && curl -sSfL https://github.com/Kitware/CMake/releases/download/v4.1.2/cmake-4.1.2-linux-x86_64.tar.gz \
      | tar xz --strip-components=1 -C /usr/local \
    && curl -sSf https://sh.rustup.rs | sh -s -- -y --profile minimal \
    && cargo install cxxbridge-cmd --version 1.0.83 --root /usr/local -j 8

RUN git clone https://github.com/Tencent/rapidjson /tmp/rapidjson \
    && git -C /tmp/rapidjson checkout 297637bc0a0f00dc504dbc1a47ebdaa577f8ae19 \
    && git clone --depth 1 -b v1.5.1 https://github.com/arun11299/cpp-jwt /tmp/cpp-jwt \
    && cp -r /tmp/rapidjson/include/rapidjson /tmp/cpp-jwt/include/jwt /usr/local/include/ \
    && rm -rf /tmp/rapidjson /tmp/cpp-jwt \
    && for f in /usr/include/rapidxml/*.hpp; do sed 's/\.hpp/.h/g' $f > /usr/local/include/$(basename ${f%.hpp}).h; done \
    && git clone --depth 1 -b v1.10.0 https://github.com/lz4/lz4 $SRC/lz4

RUN git init $SRC/scylladb \
    && git -C $SRC/scylladb remote add origin https://github.com/scylladb/scylladb.git \
    && git -C $SRC/scylladb fetch --depth 1 origin 6294ac2a14f0e7dca394d674584cb3e95b6d755c \
    && git -C $SRC/scylladb checkout FETCH_HEAD \
    && git -C $SRC/scylladb submodule update --init --recursive --depth 1 \
    && cd $SRC/scylladb && ./scripts/install-antlr3.sh
