FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libcurl4-openssl-dev rapidjson-dev libyaml-cpp-dev libpcre2-dev zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git clone --depth 1 -b v4.4.0 https://github.com/ToruNiina/toml11 /tmp/toml11 \
    && cmake -S /tmp/toml11 -B /tmp/toml11/build && cmake --install /tmp/toml11/build && rm -rf /tmp/toml11 \
    && git init /tmp/rapidjson \
    && git -C /tmp/rapidjson fetch --depth 1 https://github.com/Tencent/rapidjson 297637bc0a0f00dc504dbc1a47ebdaa577f8ae19 \
    && git -C /tmp/rapidjson checkout FETCH_HEAD && cp -r /tmp/rapidjson/include/rapidjson /usr/local/include/ && rm -rf /tmp/rapidjson \
    && git init $SRC/quickjspp \
    && git -C $SRC/quickjspp fetch --depth 1 https://github.com/ftk/quickjspp 01cdd3047ced48265b127790848a0ca88204f2c7 \
    && git -C $SRC/quickjspp checkout FETCH_HEAD \
    && git init $SRC/libcron \
    && git -C $SRC/libcron fetch --depth 1 https://github.com/PerMalmberg/libcron ee34810b11bd23c8be637345532f91059b68b2d7 \
    && git -C $SRC/libcron checkout FETCH_HEAD && git -C $SRC/libcron submodule update --init --depth 1

RUN git init $SRC/subconverter \
    && git -C $SRC/subconverter remote add origin https://github.com/tindy2013/subconverter.git \
    && git -C $SRC/subconverter fetch --depth 1 origin a0d4eab28cb8b6c782d4ce5c3a918de4829b4a72 \
    && git -C $SRC/subconverter checkout FETCH_HEAD
