FROM census-base

RUN git init $SRC/spdlog \
    && git -C $SRC/spdlog remote add origin https://github.com/gabime/spdlog.git \
    && git -C $SRC/spdlog fetch --depth 1 origin 6d9805df3f588402b17073dcd13eb569ceda864d \
    && git -C $SRC/spdlog checkout FETCH_HEAD
