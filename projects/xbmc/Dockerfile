FROM census-base

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      autoconf automake autopoint autotools-dev bison curl default-jre-headless doxygen gawk gettext gperf \
      libasound2-dev libass-dev libavahi-client-dev libavahi-common-dev libbluetooth-dev libbluray-dev \
      libbz2-dev libcdio-dev libcec-dev libcrossguid-dev libcurl4-openssl-dev libcwiid-dev libdbus-1-dev \
      libdisplay-info-dev libdrm-dev libegl1-mesa-dev libenca-dev libexiv2-dev libflac-dev \
      libflatbuffers-dev flatbuffers-compiler libfmt-dev libfontconfig-dev libfreetype6-dev libfribidi-dev \
      libfstrcmp-dev libgbm-dev libgcrypt20-dev libgif-dev libgl1-mesa-dev libgles2-mesa-dev libglew-dev \
      libglu1-mesa-dev libgnutls28-dev libgpg-error-dev libgtest-dev libinput-dev libiso9660-dev libjpeg-dev \
      liblcms2-dev liblirc-dev libltdl-dev liblzo2-dev libmicrohttpd-dev libmysqlclient-dev libnfs-dev \
      libogg-dev libpcre2-dev libplist-dev libpng-dev libpulse-dev libshairplay-dev libsmbclient-dev \
      libspdlog-dev libsqlite3-dev libssl-dev libtag1-dev libtiff5-dev libtinyxml-dev libtinyxml2-dev \
      libtool libudev-dev libunistring-dev libva-dev libvdpau-dev libvorbis-dev libwayland-dev \
      libxkbcommon-dev libxmu-dev libxrandr-dev libxslt1-dev libxt-dev lsb-release meson nasm \
      nlohmann-json3-dev python3-dev python3-pil swig unzip uuid-dev waylandpp-dev wayland-protocols \
      zip zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/xbmc \
    && git -C $SRC/xbmc remote add origin https://github.com/xbmc/xbmc.git \
    && git -C $SRC/xbmc fetch --depth 1 origin 1de3240c5b7c748eb5e5c84e3f607101f7c7f975 \
    && git -C $SRC/xbmc checkout FETCH_HEAD
