FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libgmp-dev libmpfr-dev libboost-dev libboost-program-options-dev libboost-iostreams-dev \
      libboost-serialization-dev libeigen3-dev libtbb-dev zlib1g-dev qt6-base-dev libqt6svg6-dev \
      libqt6opengl6-dev qt6-websockets-dev qt6-tools-dev libglpk-dev libmetis-dev nlohmann-json3-dev \
      libsuitesparse-dev qt6-declarative-dev libxkbcommon-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/cgal \
    && git -C $SRC/cgal remote add origin https://github.com/CGAL/cgal.git \
    && git -C $SRC/cgal fetch --depth 1 origin 44ab808c25399fc6dbd89a6e114f3fd6b5ae8142 \
    && git -C $SRC/cgal checkout FETCH_HEAD
