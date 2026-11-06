FROM census-base

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      curl unzip zip python3 python3-dev python3-numpy zlib1g-dev libssl-dev libpng-dev \
      libcurl4-openssl-dev libfftw3-dev patch \
    && rm -rf /var/lib/apt/lists/*

RUN wget -qO /usr/local/bin/bazel https://github.com/bazelbuild/bazelisk/releases/download/v1.25.0/bazelisk-linux-amd64 \
    && chmod +x /usr/local/bin/bazel

RUN git init $SRC/litert-lm \
    && git -C $SRC/litert-lm remote add origin https://github.com/google-ai-edge/LiteRT-LM.git \
    && git -C $SRC/litert-lm fetch --depth 1 origin 458390c0456e119db35d43d31862dbbf241e2c1a \
    && git -C $SRC/litert-lm checkout FETCH_HEAD
