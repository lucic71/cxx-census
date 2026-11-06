FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends curl zip unzip tar autoconf automake libtool \
    && rm -rf /var/lib/apt/lists/*

ENV VCPKG_ROOT=/vcpkg VCPKG_FORCE_SYSTEM_BINARIES=1
RUN git init $VCPKG_ROOT \
    && git -C $VCPKG_ROOT remote add origin https://github.com/microsoft/vcpkg.git \
    && git -C $VCPKG_ROOT fetch --depth 1 origin c3867e714dd3a51c272826eea77267876517ed99 \
    && git -C $VCPKG_ROOT checkout FETCH_HEAD \
    && $VCPKG_ROOT/bootstrap-vcpkg.sh -disableMetrics

RUN git init $SRC/osrm-backend \
    && git -C $SRC/osrm-backend remote add origin https://github.com/Project-OSRM/osrm-backend.git \
    && git -C $SRC/osrm-backend fetch --depth 1 origin 746c97c1c8ef7ebeb7acb9b986cf6c4e04f82caf \
    && git -C $SRC/osrm-backend checkout FETCH_HEAD

RUN $VCPKG_ROOT/vcpkg install --x-manifest-root=$SRC/osrm-backend --x-install-root=/tmp/vcpkg_installed \
      --triplet=x64-linux --only-downloads && rm -rf /tmp/vcpkg_installed
