FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends lld-23 python3 nasm yasm \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/clickhouse \
    && git -C $SRC/clickhouse remote add origin https://github.com/ClickHouse/ClickHouse.git \
    && git -C $SRC/clickhouse fetch --depth 1 origin b7920049a2e9c58a3c383da71cb0d8a835a65dd6 \
    && git -C $SRC/clickhouse checkout FETCH_HEAD \
    && git -C $SRC/clickhouse submodule update --init --depth 1 --jobs 16
