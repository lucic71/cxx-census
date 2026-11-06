FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libssl-dev libjsoncpp-dev uuid-dev zlib1g-dev libc-ares-dev libpq-dev libmariadb-dev \
      libsqlite3-dev libhiredis-dev libbrotli-dev libyaml-cpp-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/drogon \
    && git -C $SRC/drogon remote add origin https://github.com/drogonframework/drogon.git \
    && git -C $SRC/drogon fetch --depth 1 origin 553b7f32b6e761c4662eee97055e83c02430ce17 \
    && git -C $SRC/drogon checkout FETCH_HEAD \
    && git -C $SRC/drogon submodule update --init --recursive --depth 1
