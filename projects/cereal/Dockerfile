FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends libboost-serialization-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/cereal \
    && git -C $SRC/cereal remote add origin https://github.com/USCiLab/cereal.git \
    && git -C $SRC/cereal fetch --depth 1 origin 22a1b369f39be918ca79206a83c4facd759f9105 \
    && git -C $SRC/cereal checkout FETCH_HEAD
