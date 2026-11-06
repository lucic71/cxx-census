FROM census-base

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      autoconf-archive automake bison cpio cython3 flex gperf libaio-dev libbabeltrace-ctf-dev \
      libbabeltrace-dev libblkid-dev libcryptsetup-dev libcap-ng-dev libcap-dev libcunit1-dev \
      libcurl4-openssl-dev libevent-dev libexpat1-dev libfmt-dev libfuse-dev libgoogle-perftools-dev \
      libibverbs-dev libicu-dev libjerasure-dev librdmacm-dev libkeyutils-dev libldap2-dev \
      liblttng-ust-dev liblua5.3-dev liblz4-dev libnbd-dev libncurses-dev libnss3-dev liboath-dev \
      libnuma-dev libsnappy-dev libsqlite3-dev libssl-dev libtool liblmdb-dev libudev-dev \
      libnl-genl-3-dev libxml2-dev librabbitmq-dev libre2-dev libgrpc++-dev protobuf-compiler-grpc \
      libutf8proc-dev libsasl2-dev libthrift-dev libyaml-cpp-dev libzstd-dev libprotobuf-dev \
      libxsimd-dev nlohmann-json3-dev patch python3-all-dev python3-cherrypy3 python3-natsort \
      python3-jinja2 python3-markupsafe python3-pip python3-setuptools python3-wheel python3-sphinx \
      python3-venv python3-yaml systemd uuid-dev uuid-runtime valgrind xfslibs-dev nasm zlib1g-dev \
      liburing-dev libsystemd-dev curl xz-utils bzip2 \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/ceph \
    && git -C $SRC/ceph remote add origin https://github.com/ceph/ceph.git \
    && git -C $SRC/ceph fetch --depth 1 origin c9664d9cdfb84166079cbecc02cd2ac670b056a2 \
    && git -C $SRC/ceph checkout FETCH_HEAD \
    && git -C $SRC/ceph submodule update --init --recursive --depth 1

RUN curl -fsSL https://archives.boost.io/release/1.87.0/source/boost_1_87_0.tar.bz2 | tar -xj -C $SRC
