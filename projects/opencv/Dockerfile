FROM census-base

RUN git init $SRC/opencv \
    && git -C $SRC/opencv remote add origin https://github.com/opencv/opencv.git \
    && git -C $SRC/opencv fetch --depth 1 origin 205613a29728c2217049bdddbbe98322b485b34e \
    && git -C $SRC/opencv checkout FETCH_HEAD
