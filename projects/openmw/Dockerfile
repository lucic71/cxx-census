FROM census-base

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      libboost-program-options-dev libboost-system-dev libboost-iostreams-dev \
      libavcodec-dev libavformat-dev libavutil-dev libswscale-dev libswresample-dev \
      libsdl2-dev libqt6opengl6-dev qt6-tools-dev qt6-tools-dev-tools libopenal-dev \
      libunshield-dev libtinyxml-dev libbullet-dev liblz4-dev libpng-dev libjpeg-dev \
      libluajit-5.1-dev librecast-dev libsqlite3-dev libicu-dev libyaml-cpp-dev libqt6svg6-dev \
      libmygui-dev libopenscenegraph-dev libcollada-dom-dev unzip curl \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/openmw \
    && git -C $SRC/openmw remote add origin https://github.com/OpenMW/openmw.git \
    && git -C $SRC/openmw fetch --depth 1 origin f2f1f457477a4779456083a0d15c625d92dce72b \
    && git -C $SRC/openmw checkout FETCH_HEAD
