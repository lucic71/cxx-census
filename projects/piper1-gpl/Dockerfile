FROM census-base

RUN git init $SRC/piper1-gpl \
    && git -C $SRC/piper1-gpl remote add origin https://github.com/OHF-Voice/piper1-gpl.git \
    && git -C $SRC/piper1-gpl fetch --depth 1 origin 10880972db9e0aca101fed350eadf8f49deefe9f \
    && git -C $SRC/piper1-gpl checkout FETCH_HEAD
