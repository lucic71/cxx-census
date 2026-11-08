FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends autoconf automake libtool m4 texinfo \
      libglu1-mesa-dev libgtk-3-dev libdbus-1-dev libwebkit2gtk-4.1-dev libhidapi-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/prusaslicer \
    && git -C $SRC/prusaslicer remote add origin https://github.com/prusa3d/PrusaSlicer.git \
    && git -C $SRC/prusaslicer fetch --depth 1 origin ff3d6677cfccfc7fbad72acc63f01c9abec6f5d9 \
    && git -C $SRC/prusaslicer checkout FETCH_HEAD


RUN apt-get update && apt-get install -y --no-install-recommends libgmp-dev libmpfr-dev && rm -rf /var/lib/apt/lists/*
