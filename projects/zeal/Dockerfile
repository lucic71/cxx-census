FROM census-base

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      extra-cmake-modules libarchive-dev libsqlite3-dev libvulkan-dev libxcb-keysyms1-dev libxkbcommon-dev \
      libgl-dev libqt6opengl6-dev libqt6svg6-dev qt6-webengine-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/zeal \
    && git -C $SRC/zeal remote add origin https://github.com/zealdocs/zeal.git \
    && git -C $SRC/zeal fetch --depth 1 origin 1b45004ac0c0375319c88f0acfc2db8536259326 \
    && git -C $SRC/zeal checkout FETCH_HEAD
