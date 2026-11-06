FROM census-base

RUN git init $SRC/sol2 \
    && git -C $SRC/sol2 remote add origin https://github.com/ThePhD/sol2.git \
    && git -C $SRC/sol2 fetch --depth 1 origin c1f95a773c6f8f4fde8ca3efe872e7286afe4444 \
    && git -C $SRC/sol2 checkout FETCH_HEAD
