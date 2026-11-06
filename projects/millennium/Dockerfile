FROM census-base

RUN dpkg --add-architecture i386 && apt-get update && apt-get install -y --no-install-recommends \
      g++-14 gcc-14-multilib g++-14-multilib libc6-dev-i386 libgtk-3-dev libpsl-dev:i386 libssl-dev:i386 pkg-config:i386 \
      curl unzip \
    && rm -rf /var/lib/apt/lists/*

RUN curl -fsSL https://bun.sh/install | bash \
    && curl -sSf https://sh.rustup.rs | sh -s -- -y --profile minimal
ENV PATH=/root/.bun/bin:/root/.cargo/bin:$PATH

RUN git init $SRC/millennium \
    && git -C $SRC/millennium remote add origin https://github.com/SteamClientHomebrew/Millennium.git \
    && git -C $SRC/millennium fetch --depth 1 origin d6a7822a43744b6290a0e059bdd032d9b9a2ec94 \
    && git -C $SRC/millennium checkout FETCH_HEAD
