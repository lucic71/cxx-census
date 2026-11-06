FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libcurl4-openssl-dev libssl-dev libsystemd-dev gettext libgtkmm-3.0-dev qt6-svg-dev qt6-tools-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/transmission \
    && git -C $SRC/transmission remote add origin https://github.com/transmission/transmission.git \
    && git -C $SRC/transmission fetch --depth 1 origin c1a0dbebd55add20efa0bc40d8ad3c57152e5635 \
    && git -C $SRC/transmission checkout FETCH_HEAD \
    && git -C $SRC/transmission submodule update --init --recursive --depth 1
