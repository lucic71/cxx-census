FROM census-base

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      nasm python3-pip libgl-dev libegl-dev libxkbcommon-dev libfontconfig1 libfreetype6 libdbus-1-dev \
      libglib2.0-0 libx11-xcb1 libxcb-cursor0 libxcb-icccm4 libxcb-keysyms1 libxcb-shape0 \
      libxrender1 libxi6 libx11-dev libxext-dev libasound2-dev libpulse-dev libudev-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git clone --depth 1 -b n7.1.1 https://github.com/FFmpeg/FFmpeg.git $SRC/ffmpeg

RUN git init $SRC/azahar \
    && git -C $SRC/azahar remote add origin https://github.com/azahar-emu/azahar.git \
    && git -C $SRC/azahar fetch --depth 1 origin 1dfc9ed1b31a937fcd468c8fd5dc8344088b2eaf \
    && git -C $SRC/azahar checkout FETCH_HEAD \
    && git -C $SRC/azahar submodule update --init --recursive --depth 1
