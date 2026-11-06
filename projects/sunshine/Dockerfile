FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends g++-14 file glslang-tools libcap-dev libcurl4-openssl-dev \
      libdrm-dev libevdev-dev libgbm-dev libminiupnpc-dev libnuma-dev libopus-dev libpipewire-0.3-dev libpulse-dev \
      libssl-dev libsystemd-dev libudev-dev libwayland-dev libx11-dev libxcb-shm0-dev libxcb-xfixes0-dev libxcb1-dev \
      libxfixes-dev libxrandr-dev libxtst-dev libvulkan-dev libva-dev python3-jinja2 python3-venv qt6-base-dev qt6-svg-dev \
      systemd-dev udev xz-utils \
    && rm -rf /var/lib/apt/lists/*

RUN wget -qO- https://nodejs.org/dist/v22.20.0/node-v22.20.0-linux-x64.tar.xz | tar xJ --strip-components=1 -C /usr/local

RUN git init $SRC/sunshine \
    && git -C $SRC/sunshine remote add origin https://github.com/LizardByte/Sunshine.git \
    && git -C $SRC/sunshine fetch --depth 1 origin 774be88e41b5ddfe6cea5baab4ad658e3cb4adde \
    && git -C $SRC/sunshine checkout FETCH_HEAD \
    && git -C $SRC/sunshine submodule update --init --recursive --depth 1 --jobs 8
