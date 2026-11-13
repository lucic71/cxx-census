FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libx11-dev libxext-dev libxft-dev libxinerama-dev libxcursor-dev libxfixes-dev libxrender-dev libfontconfig-dev libpng-dev libjpeg-dev zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/fltk \
    && git -C $SRC/fltk remote add origin https://github.com/fltk/fltk.git \
    && git -C $SRC/fltk fetch --depth 1 origin 17b5466d891739c92127fa8d615f200d2f85bd8a \
    && git -C $SRC/fltk checkout FETCH_HEAD
