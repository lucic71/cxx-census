FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends python3-dev libeigen3-dev libboost-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/pybind11 \
    && git -C $SRC/pybind11 remote add origin https://github.com/pybind/pybind11.git \
    && git -C $SRC/pybind11 fetch --depth 1 origin 3beb3764ae967fa39dba1fe43b5a867f73da19ef \
    && git -C $SRC/pybind11 checkout FETCH_HEAD
