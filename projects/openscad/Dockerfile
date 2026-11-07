FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      bison flex gettext lib3mf-dev libboost-program-options-dev libboost-regex-dev libboost-system-dev \
      libcairo2-dev libcgal-dev libdouble-conversion-dev libeigen3-dev libffi-dev libfontconfig-dev \
      libfreetype-dev libgl1-mesa-dev libglew-dev libglib2.0-dev libgmp-dev libharfbuzz-dev \
      libmimalloc-dev libmpfr-dev libopencsg-dev libtbb-dev libxi-dev libxml2-dev libxmu-dev libssl-dev \
      libzip-dev nettle-dev python3-dev catch2 qt6-base-dev qt6-multimedia-dev libqt6svg6-dev \
      libqt6opengl6-dev libqt6core5compat6-dev libqscintilla2-qt6-dev qt6-tools-dev libegl-dev \
    && rm -rf /var/lib/apt/lists/*

RUN wget -qO- https://github.com/CGAL/cgal/releases/download/v6.0.1/CGAL-6.0.1.tar.xz | tar xJ -C /opt

RUN git init $SRC/openscad \
    && git -C $SRC/openscad remote add origin https://github.com/openscad/openscad.git \
    && git -C $SRC/openscad fetch --depth 1 origin a81e863051c42ee04168683e945aca58d32d04a2 \
    && git -C $SRC/openscad checkout FETCH_HEAD \
    && git -C $SRC/openscad submodule update --init --recursive --depth 1
