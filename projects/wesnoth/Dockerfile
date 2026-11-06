FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libboost-iostreams-dev libboost-program-options-dev libboost-regex-dev libboost-thread-dev \
      libboost-random-dev libboost-coroutine-dev libboost-locale-dev libboost-filesystem-dev \
      libboost-graph-dev libicu-dev gettext libcurl4-openssl-dev libvorbis-dev libfontconfig-dev \
      libcairo2-dev libpango1.0-dev libssl-dev libbz2-dev zlib1g-dev libreadline-dev libdbus-1-dev \
      libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev libxtst-dev \
      libxkbcommon-dev libwayland-dev wayland-protocols libdecor-0-dev libegl1-mesa-dev libgl1-mesa-dev \
      libgles2-mesa-dev libdrm-dev libgbm-dev libudev-dev libpulse-dev libasound2-dev libpng-dev libjpeg-dev libwebp-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git clone --depth 1 -b release-3.4.2 https://github.com/libsdl-org/SDL.git $SRC/SDL \
    && git clone --depth 1 -b release-3.4.0 https://github.com/libsdl-org/SDL_image.git $SRC/SDL_image \
    && git clone --depth 1 -b release-3.2.0 https://github.com/libsdl-org/SDL_mixer.git $SRC/SDL_mixer

RUN git init $SRC/wesnoth \
    && git -C $SRC/wesnoth remote add origin https://github.com/wesnoth/wesnoth.git \
    && git -C $SRC/wesnoth fetch --depth 1 origin bc78728314ea0403b0dbeecb488845fdc5822f55 \
    && git -C $SRC/wesnoth checkout FETCH_HEAD \
    && git -C $SRC/wesnoth submodule update --init --recursive --depth 1
