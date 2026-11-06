FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends python3 curl unzip \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/perfetto \
    && git -C $SRC/perfetto remote add origin https://github.com/google/perfetto.git \
    && git -C $SRC/perfetto fetch --depth 1 origin 40a170000a7228425da1249013756eb81776ec1f \
    && git -C $SRC/perfetto checkout FETCH_HEAD \
    && $SRC/perfetto/tools/install-build-deps --no-dev-tools
