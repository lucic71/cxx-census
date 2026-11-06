FROM census-base

RUN git clone https://github.com/google/brunsli.git $SRC/brunsli \
    && git -C $SRC/brunsli checkout c18b9625ef045b0b89ebb4439ae2339e2160df71 \
    && git -C $SRC/brunsli submodule update --init --recursive
