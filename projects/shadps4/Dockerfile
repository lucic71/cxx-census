FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libasound2-dev libpulse-dev libopenal-dev libssl-dev zlib1g-dev libedit-dev libudev-dev libevdev-dev \
      libsdl2-dev libjack-dev libsndio-dev libvulkan-dev vulkan-validationlayers libpng-dev libx11-dev \
      libxext-dev libxrandr-dev libxcursor-dev libxi-dev libxss-dev libxtst-dev libxkbcommon-dev \
      libwayland-dev wayland-protocols libegl-dev libdecor-0-dev python3 g++-14 libstdc++-14-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/shadps4 \
    && git -C $SRC/shadps4 remote add origin https://github.com/shadps4-emu/shadPS4.git \
    && git -C $SRC/shadps4 fetch --depth 1 origin 68b4c0c071b4172a94c6dd145706663fb58a202e \
    && git -C $SRC/shadps4 checkout FETCH_HEAD \
    && git -C $SRC/shadps4 submodule update --init --recursive --depth 1
