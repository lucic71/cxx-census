FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libx11-dev libxrandr-dev libxcursor-dev libxi-dev libudev-dev libgl-dev libfreetype-dev libflac-dev libvorbis-dev libogg-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/sfml \
    && git -C $SRC/sfml remote add origin https://github.com/SFML/SFML.git \
    && git -C $SRC/sfml fetch --depth 1 origin 697745c6236d7f3b71ca89995d73b20e2ae35401 \
    && git -C $SRC/sfml checkout FETCH_HEAD
