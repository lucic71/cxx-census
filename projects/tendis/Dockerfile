FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends autoconf \
    && rm -rf /var/lib/apt/lists/*

RUN git config --global user.name census && git config --global user.email census@localhost

RUN git init $SRC/tendis \
    && git -C $SRC/tendis remote add origin https://github.com/Tencent/Tendis.git \
    && git -C $SRC/tendis fetch --depth 1 origin 1facda08f13f7356712cd6b1fd651bce09bd62ca \
    && git -C $SRC/tendis checkout FETCH_HEAD \
    && git -C $SRC/tendis submodule update --init --recursive --depth 1
