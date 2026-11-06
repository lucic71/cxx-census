FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends libhwloc-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/onetbb \
    && git -C $SRC/onetbb remote add origin https://github.com/uxlfoundation/oneTBB.git \
    && git -C $SRC/onetbb fetch --depth 1 origin c5557dce7d5a299c7dbefe1ef39ee26bc16fbfb1 \
    && git -C $SRC/onetbb checkout FETCH_HEAD
