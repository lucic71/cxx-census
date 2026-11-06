FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      binutils dpkg-dev libssl-dev libx11-dev libxext-dev libxft-dev libxpm-dev \
      python3 python3-dev python3-numpy libtbb-dev libvdt-dev libgif-dev libpcre2-dev \
      libglu1-mesa-dev libglew-dev libftgl-dev libfftw3-dev libcfitsio-dev libgraphviz-dev \
      libldap2-dev libxml2-dev libkrb5-dev libgsl-dev nlohmann-json3-dev libgl2ps-dev \
      liblzma-dev libxxhash-dev liblz4-dev libzstd-dev zlib1g-dev libfreetype-dev \
      libjpeg-dev libpng-dev libtiff-dev libcurl4-openssl-dev gfortran \
      libxrootd-client-dev libxrootd-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/root \
    && git -C $SRC/root remote add origin https://github.com/root-project/root.git \
    && git -C $SRC/root fetch --depth 1 origin 76948cf3c3528f27f4fad538baf2e28f48eda1ac \
    && git -C $SRC/root checkout FETCH_HEAD
