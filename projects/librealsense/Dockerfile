FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libusb-1.0-0-dev libudev-dev libssl-dev libgtk-3-dev libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev \
      libcurl4-openssl-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/librealsense \
    && git -C $SRC/librealsense remote add origin https://github.com/realsenseai/librealsense.git \
    && git -C $SRC/librealsense fetch --depth 1 origin c84fe6438bd14a4cc69f46deae92c993268232c6 \
    && git -C $SRC/librealsense checkout FETCH_HEAD
