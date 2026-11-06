FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends libcurl4-openssl-dev libssl-dev python3 \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/runanywhere-sdks \
    && git -C $SRC/runanywhere-sdks remote add origin https://github.com/RunanywhereAI/runanywhere-sdks.git \
    && git -C $SRC/runanywhere-sdks fetch --depth 1 origin 87865ea825d131498cf255b129ae81f26449e637 \
    && git -C $SRC/runanywhere-sdks checkout FETCH_HEAD
