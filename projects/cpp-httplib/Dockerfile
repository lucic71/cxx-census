FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends python3 openssl libssl-dev zlib1g-dev \
      libbrotli-dev libzstd-dev libcurl4-openssl-dev libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/cpp-httplib \
    && git -C $SRC/cpp-httplib remote add origin https://github.com/yhirose/cpp-httplib.git \
    && git -C $SRC/cpp-httplib fetch --depth 1 origin 7e5d0683ac326788e52ce3c44585c1af24b04532 \
    && git -C $SRC/cpp-httplib checkout FETCH_HEAD
