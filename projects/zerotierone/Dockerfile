FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends curl libssl-dev \
    && rm -rf /var/lib/apt/lists/*

RUN curl -sSf https://sh.rustup.rs | sh -s -- -y --profile minimal
ENV PATH=/root/.cargo/bin:$PATH

RUN git init $SRC/zerotierone \
    && git -C $SRC/zerotierone remote add origin https://github.com/zerotier/ZeroTierOne.git \
    && git -C $SRC/zerotierone fetch --depth 1 origin 899352e38405968516bb12a770f0ac02f6058fa8 \
    && git -C $SRC/zerotierone checkout FETCH_HEAD
