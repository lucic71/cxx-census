FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git clone https://gitlab.com/saalen/astyle.git $SRC/astyle \
    && git -C $SRC/astyle checkout 7f531db503617040a0c31be5f551220ec54dc47e
