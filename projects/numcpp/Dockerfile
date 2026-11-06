FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libboost-date-time-dev libboost-log-dev python3-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/numcpp \
    && git -C $SRC/numcpp remote add origin https://github.com/dpilger26/NumCpp.git \
    && git -C $SRC/numcpp fetch --depth 1 origin 8c43694c0253d27f0cc4bded1394290172c037c9 \
    && git -C $SRC/numcpp checkout FETCH_HEAD
