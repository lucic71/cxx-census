FROM census-base

RUN git init $SRC/protobuf \
    && git -C $SRC/protobuf remote add origin https://github.com/protocolbuffers/protobuf.git \
    && git -C $SRC/protobuf fetch --depth 1 origin 6550349ef293d60a8ad58aba4d08edf860f25f03 \
    && git -C $SRC/protobuf checkout FETCH_HEAD \
    && git -C $SRC/protobuf submodule update --init --recursive --depth 1
