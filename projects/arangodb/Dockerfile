FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      bison flex libomp-23-dev lld-23 libopenblas-dev liblapack-dev libssl-dev python3 python3-setuptools zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/arangodb \
    && git -C $SRC/arangodb remote add origin https://github.com/arangodb/arangodb.git \
    && git -C $SRC/arangodb fetch --depth 1 origin aaf43d548368e421fbf57abf4add4f5e6cf25c6d \
    && git -C $SRC/arangodb checkout FETCH_HEAD \
    && git -C $SRC/arangodb submodule update --init --recursive --depth 1
