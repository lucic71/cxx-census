FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends catch2 libboost-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/cli11 \
    && git -C $SRC/cli11 remote add origin https://github.com/CLIUtils/CLI11.git \
    && git -C $SRC/cli11 fetch --depth 1 origin 1764a057b760e8873eab03f4635b4aaed5303a04 \
    && git -C $SRC/cli11 checkout FETCH_HEAD
