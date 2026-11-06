FROM vesoft/nebula-dev:ubuntu2004 AS dev

FROM census-base

COPY --from=dev /opt/vesoft/third-party/3.3 /opt/vesoft/third-party/3.3

RUN apt-get update && apt-get install -y --no-install-recommends m4 python3 \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/nebula \
    && git -C $SRC/nebula remote add origin https://github.com/vesoft-inc/nebula.git \
    && git -C $SRC/nebula fetch --depth 1 origin 426266b5c3df856d27f747b55b916dec542b7b59 \
    && git -C $SRC/nebula checkout FETCH_HEAD
