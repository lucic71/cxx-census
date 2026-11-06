FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends libcurl4-openssl-dev libssl-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/cpr \
    && git -C $SRC/cpr remote add origin https://github.com/libcpr/cpr.git \
    && git -C $SRC/cpr fetch --depth 1 origin cdbbd90fb01c29dd52ed3e19f606bb4980e71541 \
    && git -C $SRC/cpr checkout FETCH_HEAD
