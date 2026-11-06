FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libasound2-dev libpulse-dev libjack-jackd2-dev libsndio-dev libx11-dev libxext-dev libxrandr-dev \
      libxcursor-dev libxfixes-dev libxi-dev libxss-dev libxtst-dev libxkbcommon-dev libdrm-dev libgbm-dev \
      libgl1-mesa-dev libegl-dev libgles-dev libdbus-1-dev libudev-dev libpipewire-0.3-dev libwayland-dev \
      libdecor-0-dev liburing-dev python3 python3-clang-23 rustc-1.91 cargo-1.91 \
    && rm -rf /var/lib/apt/lists/*

ENV PATH=/usr/lib/rust-1.91/bin:$PATH

RUN git init $SRC/sogen \
    && git -C $SRC/sogen remote add origin https://github.com/momo5502/sogen.git \
    && git -C $SRC/sogen fetch --depth 1 origin c3e4b57bed316c29cd0b05a1f32f2d12d782d05a \
    && git -C $SRC/sogen checkout FETCH_HEAD \
    && git -C $SRC/sogen submodule update --init --recursive --depth 1
