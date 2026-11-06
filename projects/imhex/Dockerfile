FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libstdc++-14-dev libgl-dev libglu1-mesa-dev libwayland-dev libwayland-bin libxkbcommon-dev \
      libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libxext-dev libglm-dev \
      libmagic-dev libfontconfig-dev libfreetype-dev libdbus-1-dev libcurl4-gnutls-dev libgtk-3-dev \
      zlib1g-dev libbz2-dev liblzma-dev libzstd-dev liblz4-dev libssh2-1-dev libmd4c-dev \
      libmd4c-html0-dev libelf-dev python3 \
    && rm -rf /var/lib/apt/lists/*

RUN wget -qO- https://github.com/Mbed-TLS/mbedtls/releases/download/mbedtls-3.6.4/mbedtls-3.6.4.tar.bz2 | tar xj -C /opt

RUN git init $SRC/imhex \
    && git -C $SRC/imhex remote add origin https://github.com/WerWolv/ImHex.git \
    && git -C $SRC/imhex fetch --depth 1 origin 34483cb90527cd71c92049ef3b1b2cc27936a1d4 \
    && git -C $SRC/imhex checkout FETCH_HEAD \
    && git -C $SRC/imhex submodule update --init --recursive --depth 1
