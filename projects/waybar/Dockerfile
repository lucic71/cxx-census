FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      meson scdoc catch2 wayland-protocols libwayland-dev libgtkmm-3.0-dev libdbusmenu-gtk3-dev \
      libgtk-layer-shell-dev libjsoncpp-dev libfmt-dev libspdlog-dev libinput-dev libnl-3-dev \
      libnl-genl-3-dev libupower-glib-dev libpipewire-0.3-dev libplayerctl-dev libpulse-dev libudev-dev \
      libevdev-dev libmpdclient-dev libxkbregistry-dev libxkbcommon-dev libjack-jackd2-dev libgps-dev \
      libmm-glib-dev libsndio-dev libsystemd-dev libhowardhinnant-date-dev libiniparser-dev libfftw3-dev \
      libepoxy-dev libasound2-dev libpugixml-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/waybar \
    && git -C $SRC/waybar remote add origin https://github.com/Alexays/Waybar.git \
    && git -C $SRC/waybar fetch --depth 1 origin f49ec82e2d296f033b081fd36d12297795b017dc \
    && git -C $SRC/waybar checkout FETCH_HEAD
