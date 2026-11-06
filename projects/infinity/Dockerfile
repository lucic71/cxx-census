FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends software-properties-common gpg-agent \
    && add-apt-repository -y ppa:ubuntu-toolchain-r/test \
    && apt-get install -y --no-install-recommends g++-15 mold lld-23 flex bison autoconf autoconf-archive automake libtool \
      curl zip unzip tar python3 linux-libc-dev \
    && rm -rf /var/lib/apt/lists/*

RUN wget -qO- https://github.com/Kitware/CMake/releases/download/v4.2.5/cmake-4.2.5-linux-x86_64.tar.gz \
    | tar xz --strip-components=1 -C /usr/local

RUN git init $SRC/infinity \
    && git -C $SRC/infinity remote add origin https://github.com/infiniflow/infinity.git \
    && git -C $SRC/infinity fetch --depth 1 origin 2fffa346354fb66d69374b4ad7ae040cbae0f731 \
    && git -C $SRC/infinity checkout FETCH_HEAD

ENV VCPKG_ROOT=/opt/vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git $VCPKG_ROOT \
    && git -C $VCPKG_ROOT checkout aa40adda5352e87655b8583cfb2451d5e9e276fd \
    && $VCPKG_ROOT/bootstrap-vcpkg.sh -disableMetrics \
    && cd $SRC/infinity && $VCPKG_ROOT/vcpkg install --overlay-ports=ports --only-downloads --x-install-root=/tmp/vi \
    && rm -rf /tmp/vi
