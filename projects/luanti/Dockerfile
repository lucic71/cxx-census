FROM census-base

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      libc6-dev libpng-dev libjpeg-dev libgl1-mesa-dev libsqlite3-dev libogg-dev libvorbis-dev libopenal-dev \
      libcurl4-gnutls-dev libfreetype6-dev zlib1g-dev libgmp-dev libjsoncpp-dev libzstd-dev \
      libluajit-5.1-dev gettext libsdl2-dev libzip-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/luanti \
    && git -C $SRC/luanti remote add origin https://github.com/luanti-org/luanti.git \
    && git -C $SRC/luanti fetch --depth 1 origin b4c73357a6159e48810dea24428f3ebaa24dd345 \
    && git -C $SRC/luanti checkout FETCH_HEAD
