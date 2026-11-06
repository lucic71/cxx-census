FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libasound2-dev libsoxr-dev libvorbisidec-dev libvorbis-dev libflac-dev libopus-dev \
      libpulse-dev libavahi-client-dev libssl-dev libexpat1-dev libboost-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/snapcast \
    && git -C $SRC/snapcast remote add origin https://github.com/snapcast/snapcast.git \
    && git -C $SRC/snapcast fetch --depth 1 origin ea981ec5ec0805dfc9b4af3979090c325abf501d \
    && git -C $SRC/snapcast checkout FETCH_HEAD
