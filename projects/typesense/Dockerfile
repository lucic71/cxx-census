FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends python3 python-is-python3 zlib1g-dev m4 lld unzip zip curl \
    && rm -rf /var/lib/apt/lists/*

RUN wget -qO /usr/local/bin/bazel https://github.com/bazelbuild/bazelisk/releases/download/v1.25.0/bazelisk-linux-amd64 \
    && chmod +x /usr/local/bin/bazel

RUN git init $SRC/typesense \
    && git -C $SRC/typesense remote add origin https://github.com/typesense/typesense.git \
    && git -C $SRC/typesense fetch --depth 1 origin 3423e2e0daf335a38135aaf20032ce5664497908 \
    && git -C $SRC/typesense checkout FETCH_HEAD \
    && cd $SRC/typesense && bazel --version
