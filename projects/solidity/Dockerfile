FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libboost-dev libboost-filesystem-dev libboost-program-options-dev libboost-test-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/solidity \
    && git -C $SRC/solidity remote add origin https://github.com/argotorg/solidity.git \
    && git -C $SRC/solidity fetch --depth 1 origin 2ec5173f2b6366832dede8b4fcd958f5c211d1a1 \
    && git -C $SRC/solidity checkout FETCH_HEAD \
    && git -C $SRC/solidity submodule update --init --recursive --depth 1
