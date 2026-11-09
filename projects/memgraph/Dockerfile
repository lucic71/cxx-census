FROM census-base

RUN wget -qO /etc/apt/trusted.gpg.d/toolchain.asc \
      "https://keyserver.ubuntu.com/pks/lookup?op=get&search=0x60C317803A41BA51845E371A1E9377A2BA9EF27F" \
    && echo "deb https://ppa.launchpadcontent.net/ubuntu-toolchain-r/test/ubuntu noble main" \
      > /etc/apt/sources.list.d/toolchain.list \
    && apt-get update && apt-get install -y --no-install-recommends \
      g++-15 libstdc++-15-dev lld-23 gperf libreadline-dev libpython3-dev python3-dev python3-venv python3-pip \
      python3-yaml patchelf libssl-dev autoconf libtool libkrb5-dev rustc-1.91 cargo-1.91 \
    && rm -rf /var/lib/apt/lists/*

RUN python3 -m venv /opt/conan && /opt/conan/bin/pip install "conan>=2.26.0"
ENV PATH=/opt/conan/bin:/usr/lib/rust-1.91/bin:/usr/lib/llvm-23/bin:$PATH

RUN git init $SRC/memgraph \
    && git -C $SRC/memgraph remote add origin https://github.com/memgraph/memgraph.git \
    && git -C $SRC/memgraph fetch --depth 1 origin 08d2ade3c96bc2e4905594873d391eb88db72ada \
    && git -C $SRC/memgraph checkout FETCH_HEAD \
    && ln -s clang-23 /usr/bin/clang && ln -s clang++-23 /usr/bin/clang++

RUN cd $SRC/memgraph && conan profile detect && conan config install conan_config \
    && conan remote add memgraph-recipes $SRC/memgraph/conan_recipes -t local-recipes-index \
    && for i in $(seq 30); do conan graph info . -pr:h default -pr:h memgraph_linux_base -pr:b memgraph_build_profile \
       -s build_type=Release -s os.distro=ubuntu-24.04 -o "&:bundled_toolchain=False" --lockfile-partial \
       -c tools.build:download_source=True > /dev/null && exit 0; sleep 60; done; exit 1
