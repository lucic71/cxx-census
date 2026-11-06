FROM census-base

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends libboost-dev libssl-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/libtorrent \
    && git -C $SRC/libtorrent remote add origin https://github.com/arvidn/libtorrent.git \
    && git -C $SRC/libtorrent fetch --depth 1 origin 86d573f2631b0162d3cca5e257217eaf530fdcba \
    && git -C $SRC/libtorrent checkout FETCH_HEAD \
    && git -C $SRC/libtorrent submodule update --init --recursive --depth 1
