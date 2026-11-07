FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends software-properties-common gpg-agent \
    && add-apt-repository -y ppa:ubuntu-toolchain-r/test \
    && apt-get update && apt-get install -y --no-install-recommends libstdc++-15-dev python3-pip perl \
    && rm -rf /var/lib/apt/lists/* \
    && pip3 install --break-system-packages --no-cache-dir conan \
    && ln -s /usr/bin/clang-23 /usr/local/bin/clang && ln -s /usr/bin/clang++-23 /usr/local/bin/clang++

RUN git init $SRC/rippled \
    && git -C $SRC/rippled remote add origin https://github.com/XRPLF/rippled.git \
    && git -C $SRC/rippled fetch --depth 1 origin 5fc24fcd10da3901e90364284d3a9900abbc8763 \
    && git -C $SRC/rippled checkout FETCH_HEAD \
    && $SRC/rippled/conan/init.sh
