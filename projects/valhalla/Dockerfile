FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libboost-dev libcurl4-openssl-dev libczmq-dev libzmq3-dev libgeos-dev libluajit-5.1-dev \
      liblz4-dev libprotobuf-dev protobuf-compiler libspatialite-dev libsqlite3-dev libssl-dev \
      libexpat1-dev libgeotiff-dev libtiff-dev python3-dev zlib1g-dev spatialite-bin \
    && rm -rf /var/lib/apt/lists/*

RUN git clone --depth 1 -b 0.12.0 --recurse-submodules https://github.com/kevinkreiser/prime_server $SRC/prime_server

RUN git init $SRC/valhalla \
    && git -C $SRC/valhalla remote add origin https://github.com/valhalla/valhalla.git \
    && git -C $SRC/valhalla fetch --depth 1 origin 30dc99585fd35ff74b07141b86e1d2cc728b6b06 \
    && git -C $SRC/valhalla checkout FETCH_HEAD \
    && git -C $SRC/valhalla submodule update --init --recursive --depth 1
