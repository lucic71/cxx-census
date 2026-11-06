FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libjack-jackd2-dev libsndfile1-dev libasound2-dev libavahi-client-dev libreadline-dev libfftw3-dev \
      libicu-dev libxt-dev libudev-dev libncurses-dev emacs-nox \
      libboost-thread-dev libboost-system-dev libboost-filesystem-dev libboost-regex-dev libboost-test-dev \
      libboost-program-options-dev libyaml-cpp-dev \
      qt6-base-dev qt6-base-dev-tools qt6-tools-dev qt6-tools-dev-tools qt6-declarative-dev libqt6svgwidgets6 \
      qt6-webengine-dev qt6-webengine-dev-tools linguist-qt6 qt6-l10n-tools libglx-dev libgl1-mesa-dev \
      libvulkan-dev libxkbcommon-dev libxcb-xkb-dev libqt6opengl6-dev libqt6svg6-dev \
      libqt6webchannel6-dev libqt6websockets6-dev libstdc++-14-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/supercollider \
    && git -C $SRC/supercollider remote add origin https://github.com/supercollider/supercollider.git \
    && git -C $SRC/supercollider fetch --depth 1 origin 0c5a96d701be992627b40367f9540b67624120f0 \
    && git -C $SRC/supercollider checkout FETCH_HEAD \
    && git -C $SRC/supercollider submodule update --init --recursive --depth 1
