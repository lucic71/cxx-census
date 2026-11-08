FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libdnnl-dev libgloo-dev libopenmpi-dev openmpi-bin libcereal-dev libstb-dev libgtest-dev libgmock-dev libfmt-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/flashlight \
    && git -C $SRC/flashlight remote add origin https://github.com/flashlight/flashlight.git \
    && git -C $SRC/flashlight fetch --depth 1 origin 1bb22bba16992becfba721ca4a7385fbd3c81eab \
    && git -C $SRC/flashlight checkout FETCH_HEAD
