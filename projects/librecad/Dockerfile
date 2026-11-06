FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      qt6-base-dev qt6-svg-dev qt6-tools-dev qt6-l10n-tools linguist-qt6 \
      libmuparser-dev libboost-dev libfreetype-dev libgl-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/librecad \
    && git -C $SRC/librecad remote add origin https://github.com/LibreCAD/LibreCAD.git \
    && git -C $SRC/librecad fetch --depth 1 origin e2a8c29311a4a9dea52aeb0ad0f73440d80a1f16 \
    && git -C $SRC/librecad checkout FETCH_HEAD \
    && git -C $SRC/librecad submodule update --init --recursive --depth 1
