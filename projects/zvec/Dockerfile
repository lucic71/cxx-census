FROM census-base

RUN git init $SRC/zvec \
    && git -C $SRC/zvec remote add origin https://github.com/alibaba/zvec.git \
    && git -C $SRC/zvec fetch --depth 1 origin 30d662db4d2467937d843443074b34743bcc9baa \
    && git -C $SRC/zvec checkout FETCH_HEAD \
    && git -C $SRC/zvec submodule update --init --recursive --depth 1
