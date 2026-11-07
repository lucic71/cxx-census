FROM census-base

RUN wget -qO /etc/apt/trusted.gpg.d/toolchain.asc \
      'https://keyserver.ubuntu.com/pks/lookup?op=get&search=0x60C317803A41BA51845E371A1E9377A2BA9EF27F' \
    && echo 'deb https://ppa.launchpadcontent.net/ubuntu-toolchain-r/test/ubuntu noble main' \
      > /etc/apt/sources.list.d/toolchain.list \
    && apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      libstdc++-15-dev python3-venv libgl-dev libegl-dev libfontconfig1-dev libfreetype-dev \
      libglib2.0-dev libdbus-1-dev libx11-dev libx11-xcb-dev libxcb1-dev libxcb-keysyms1-dev libxcb-xkb-dev \
      libxcb-cursor-dev libxkbcommon-dev libxkbcommon-x11-dev libwayland-dev libssl-dev libsecret-1-dev \
      libqalculate-dev libudev-dev extra-cmake-modules wayland-protocols xz-utils zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

RUN python3 -m venv /tmp/aqt && /tmp/aqt/bin/pip install --no-cache-dir aqtinstall \
    && /tmp/aqt/bin/aqt install-qt linux desktop 6.10.1 linux_gcc_64 -m qtshadertools -O /opt/Qt \
    && rm -rf /tmp/aqt

RUN mkdir /opt/node && wget -qO- https://nodejs.org/dist/v22.23.1/node-v22.23.1-linux-x64.tar.xz \
    | tar xJ --strip-components=1 -C /opt/node

ENV CMAKE_PREFIX_PATH=/opt/Qt/6.10.1/gcc_64 PATH=/opt/node/bin:$PATH

RUN git init $SRC/vicinae \
    && git -C $SRC/vicinae remote add origin https://github.com/vicinaehq/vicinae.git \
    && git -C $SRC/vicinae fetch --depth 1 origin 0ed7dcce1f530067aa251d1beab1a57760e385b4 \
    && git -C $SRC/vicinae checkout FETCH_HEAD
