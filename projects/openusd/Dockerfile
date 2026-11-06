FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libtbb-dev python3-dev python3-jinja2 libgl-dev libx11-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git clone --depth 1 -b v3_6_1 https://github.com/PixarAnimationStudios/OpenSubdiv.git $SRC/opensubdiv

RUN git init $SRC/openusd \
    && git -C $SRC/openusd remote add origin https://github.com/PixarAnimationStudios/OpenUSD.git \
    && git -C $SRC/openusd fetch --depth 1 origin 2d39590aac6dde875507d2a334ff6e5b9dc05fe1 \
    && git -C $SRC/openusd checkout FETCH_HEAD
