FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libssl-dev libzmq3-dev libunbound-dev libsodium-dev libunwind-dev libhidapi-dev libusb-1.0-0-dev \
      libprotobuf-dev protobuf-compiler libboost-chrono-dev libboost-date-time-dev libboost-filesystem-dev \
      libboost-locale-dev libboost-program-options-dev libboost-regex-dev libboost-serialization-dev \
      libboost-system-dev libboost-thread-dev python3 rustc-1.91 cargo-1.91 \
    && rm -rf /var/lib/apt/lists/*

ENV PATH=/usr/lib/rust-1.91/bin:$PATH

RUN git init $SRC/monero \
    && git -C $SRC/monero remote add origin https://github.com/monero-project/monero.git \
    && git -C $SRC/monero fetch --depth 1 origin b14fae7bca4099cea56205e44c1005602834b7bd \
    && git -C $SRC/monero checkout FETCH_HEAD \
    && git -C $SRC/monero submodule update --init --recursive --depth 1
