FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends libncurses-dev zlib1g-dev gettext \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/cataclysm-dda \
    && git -C $SRC/cataclysm-dda remote add origin https://github.com/CleverRaven/Cataclysm-DDA.git \
    && git -C $SRC/cataclysm-dda fetch --depth 1 origin 06be12f9884d82d387cb6b38dc549eca71c3835a \
    && git -C $SRC/cataclysm-dda checkout FETCH_HEAD
