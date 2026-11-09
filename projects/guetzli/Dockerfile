FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends libpng-dev libgflags-dev netpbm libjpeg-turbo-progs \
    && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/google/guetzli.git $SRC/guetzli \
    && git -C $SRC/guetzli checkout 214f2bb42abf5a577c079d00add5d6cc470620d3
