FROM census-base

RUN wget -qO /etc/apt/trusted.gpg.d/arrayfire.asc https://repo.arrayfire.com/GPG-PUB-KEY-ARRAYFIRE-2020.PUB \
    && echo "deb [arch=amd64] https://repo.arrayfire.com/debian all main" > /etc/apt/sources.list.d/arrayfire.list \
    && apt-get update && apt-get install -y --no-install-recommends \
      arrayfire-cmake=3.9.0-1 arrayfire-headers=3.9.0-1 arrayfire-cpu3-openblas=3.9.0-1 arrayfire-cpu3-dev=3.9.0-1 \
      libdnnl-dev libgloo-dev libopenmpi-dev openmpi-bin libcereal-dev libstb-dev libgtest-dev libgmock-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/flashlight \
    && git -C $SRC/flashlight remote add origin https://github.com/flashlight/flashlight.git \
    && git -C $SRC/flashlight fetch --depth 1 origin 1bb22bba16992becfba721ca4a7385fbd3c81eab \
    && git -C $SRC/flashlight checkout FETCH_HEAD
