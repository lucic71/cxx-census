FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends libssl-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/pcm \
    && git -C $SRC/pcm remote add origin https://github.com/intel/pcm.git \
    && git -C $SRC/pcm fetch --depth 1 origin 96751b666e91b29660a63237b300ea0521ab4fcd \
    && git -C $SRC/pcm checkout FETCH_HEAD \
    && git -C $SRC/pcm submodule update --init --recursive --depth 1
