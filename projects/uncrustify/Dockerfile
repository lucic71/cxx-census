FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends python3 \
    && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/uncrustify/uncrustify.git $SRC/uncrustify \
    && git -C $SRC/uncrustify checkout efb1d76f97448bf64e807548d94248dfd937ac73
