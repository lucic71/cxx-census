FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends libbrotli-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/google/woff2.git $SRC/woff2 \
    && git -C $SRC/woff2 checkout 7b67e12355fe7da148db5c19d4261f0a498a9537
