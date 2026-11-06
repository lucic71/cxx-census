FROM census-base

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      libgl1-mesa-dev libglvnd-dev libharfbuzz-dev libqt6svg6-dev libxcursor-dev libxi-dev \
      libxinerama-dev libxrandr-dev qt6-base-dev qt6-l10n-tools qt6-positioning-dev qt6-tools-dev \
      qt6-translations-l10n python3 \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/organicmaps \
    && git -C $SRC/organicmaps remote add origin https://github.com/organicmaps/organicmaps.git \
    && git -C $SRC/organicmaps fetch --depth 1 origin 314bbe794129815118fc8267073abc59f8a9ac71 \
    && git -C $SRC/organicmaps checkout FETCH_HEAD \
    && git -C $SRC/organicmaps submodule update --init --recursive --depth 1
