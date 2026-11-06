FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libjpeg-dev libtiff-dev libpng-dev zlib1g-dev liblapack-dev libblas-dev libfftw3-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/matplotplusplus \
    && git -C $SRC/matplotplusplus remote add origin https://github.com/alandefreitas/matplotplusplus.git \
    && git -C $SRC/matplotplusplus fetch --depth 1 origin 2ccbb7ff86295bb4d3aca2938dce09ca3accb1ef \
    && git -C $SRC/matplotplusplus checkout FETCH_HEAD
