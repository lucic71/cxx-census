FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev zlib1g-dev libavformat-dev libswscale-dev \
      libboost-dev libboost-filesystem-dev libboost-program-options-dev libboost-date-time-dev \
      libboost-iostreams-dev libboost-locale-dev libboost-thread-dev qt6-base-dev qt6-base-dev-tools qt6-tools-dev \
      qt6-tools-dev-tools qt6-l10n-tools qt6-svg-dev libtbb-dev libluajit-5.1-dev liblzma-dev libsqlite3-dev \
      libminizip-dev libsquish-dev libfmt-dev libcurl4-openssl-dev gettext \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /opt/onnxruntime \
    && wget -qO- https://github.com/microsoft/onnxruntime/releases/download/v1.18.1/onnxruntime-linux-x64-1.18.1.tgz \
       | tar -xz --strip-components=1 -C /opt/onnxruntime

RUN git init $SRC/vcmi \
    && git -C $SRC/vcmi remote add origin https://github.com/vcmi/vcmi.git \
    && git -C $SRC/vcmi fetch --depth 1 origin cfdf594f9bd9f697fef4ce9bdb5cc125ed5983e6 \
    && git -C $SRC/vcmi checkout FETCH_HEAD \
    && git -C $SRC/vcmi submodule update --init --recursive --depth 1
