FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      autoconf automake libpcre2-dev libsqlite3-dev zlib1g-dev libbz2-dev libcurl4-openssl-dev \
      libarchive-dev libunistring-dev libncurses-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/lnav \
    && git -C $SRC/lnav remote add origin https://github.com/tstack/lnav.git \
    && git -C $SRC/lnav fetch --depth 1 origin e6631e4e7acf71ea59e899b8678b9d88ebfbf413 \
    && git -C $SRC/lnav checkout FETCH_HEAD
