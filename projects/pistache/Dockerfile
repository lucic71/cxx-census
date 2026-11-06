FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends meson rapidjson-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/pistache \
    && git -C $SRC/pistache remote add origin https://github.com/pistacheio/pistache.git \
    && git -C $SRC/pistache fetch --depth 1 origin a7b0dc9ec01b96b95bde55331d83e27a9bf800b9 \
    && git -C $SRC/pistache checkout FETCH_HEAD
