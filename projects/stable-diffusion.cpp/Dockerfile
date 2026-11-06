FROM census-base

RUN git init $SRC/stable-diffusion.cpp \
    && git -C $SRC/stable-diffusion.cpp remote add origin https://github.com/leejet/stable-diffusion.cpp.git \
    && git -C $SRC/stable-diffusion.cpp fetch --depth 1 origin f5df5f8b84f139f1e80496902da90798a0d92896 \
    && git -C $SRC/stable-diffusion.cpp checkout FETCH_HEAD \
    && git -C $SRC/stable-diffusion.cpp submodule update --init --recursive --depth 1
