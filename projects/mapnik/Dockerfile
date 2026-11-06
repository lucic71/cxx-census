FROM census-base

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      libicu-dev libfreetype6-dev libharfbuzz-dev libxml2-dev libjpeg-dev libtiff-dev libwebp-dev \
      libavif-dev libcairo2-dev libproj-dev libgdal-dev libboost-filesystem-dev \
      libboost-program-options-dev libboost-regex-dev libboost-url-dev libboost-context-dev \
      libssl-dev libpq-dev libsqlite3-dev qt6-base-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/mapnik \
    && git -C $SRC/mapnik remote add origin https://github.com/mapnik/mapnik.git \
    && git -C $SRC/mapnik fetch --depth 1 origin 195f7bfa211d1d3d35328f530307b6a4949f4b7b \
    && git -C $SRC/mapnik checkout FETCH_HEAD \
    && git -C $SRC/mapnik submodule update --init --recursive --depth 1
