FROM census-base

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends libssl-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/actor-framework \
    && git -C $SRC/actor-framework remote add origin https://github.com/actor-framework/actor-framework.git \
    && git -C $SRC/actor-framework fetch --depth 1 origin 44ea874193e417a31edaf1ffaa55828e0a79016b \
    && git -C $SRC/actor-framework checkout FETCH_HEAD
