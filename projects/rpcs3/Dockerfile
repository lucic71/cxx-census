FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libasound2-dev libpulse-dev libopenal-dev libglew-dev zlib1g-dev libedit-dev libvulkan-dev \
      libudev-dev libevdev-dev libjack-dev libsndio-dev libcurl4-openssl-dev libxkbcommon-dev \
      libxkbcommon-x11-dev libxcursor-dev libxi-dev libxrandr-dev libxss-dev libxtst-dev libxfixes-dev \
      libgl-dev libegl-dev libwayland-dev libx11-dev libxext-dev python3-pip python3-venv \
    && rm -rf /var/lib/apt/lists/*

RUN python3 -m venv /opt/aqt && /opt/aqt/bin/pip install --no-cache-dir aqtinstall \
    && /opt/aqt/bin/aqt install-qt linux desktop 6.12.0 linux_gcc_64 -m qtmultimedia -O /opt/Qt \
    && rm -rf /opt/aqt

ENV Qt6_ROOT=/opt/Qt/6.12.0/gcc_64

RUN git init $SRC/rpcs3 \
    && git -C $SRC/rpcs3 remote add origin https://github.com/RPCS3/rpcs3.git \
    && git -C $SRC/rpcs3 fetch --depth 1 origin eee3f0f7c285f2b8aa18fec278a2146c5cd874eb \
    && git -C $SRC/rpcs3 checkout FETCH_HEAD \
    && git -C $SRC/rpcs3 -c submodule.3rdparty/llvm/llvm.update=none submodule update --init --recursive --depth 1

RUN apt-get update && apt-get install -y --no-install-recommends libfontconfig1 libfreetype6 \
    && rm -rf /var/lib/apt/lists/*
