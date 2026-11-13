FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      flex bison python3 \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/doxygen \
    && git -C $SRC/doxygen remote add origin https://github.com/doxygen/doxygen.git \
    && git -C $SRC/doxygen fetch --depth 1 origin 9cf369999387d8c30313c2e46699497e3e180f2e \
    && git -C $SRC/doxygen checkout FETCH_HEAD
