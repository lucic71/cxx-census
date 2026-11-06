FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends autoconf autoconf-archive automake libtool bison flex \
      curl zip unzip tar python3 python3-venv libapparmor-dev libsystemd-dev libssl-dev lld \
    && rm -rf /var/lib/apt/lists/*

RUN curl -sSf https://sh.rustup.rs | sh -s -- -y --profile minimal
ENV PATH=/root/.cargo/bin:$PATH

RUN git init $SRC/multipass \
    && git -C $SRC/multipass remote add origin https://github.com/canonical/multipass.git \
    && git -C $SRC/multipass fetch --tags origin f94816876055ceca991d02a2aeeee2a8d75f59b5 \
    && git -C $SRC/multipass checkout FETCH_HEAD \
    && git -C $SRC/multipass submodule update --init --recursive --depth 1 --jobs 8 \
    && git -C $SRC/multipass/3rd-party/vcpkg fetch --unshallow
