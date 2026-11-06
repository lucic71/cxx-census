FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends doctest-dev nlohmann-json3-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git clone --depth 1 -b 0.8.2 https://github.com/xtensor-stack/xtl.git /tmp/xtl \
    && cmake -S /tmp/xtl -B /tmp/xtl/build && cmake --install /tmp/xtl/build && rm -rf /tmp/xtl

RUN git init $SRC/xtensor \
    && git -C $SRC/xtensor remote add origin https://github.com/xtensor-stack/xtensor.git \
    && git -C $SRC/xtensor fetch --depth 1 origin 75abad508c2d9c1d99b7af72be92ec2d0da8711a \
    && git -C $SRC/xtensor checkout FETCH_HEAD
