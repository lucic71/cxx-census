FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      bison libssl-dev libncurses-dev libtirpc-dev rpcsvc-proto libldap-dev libsasl2-dev \
      libcurl4-openssl-dev libkrb5-dev libnuma-dev libudev-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/mysql-server \
    && git -C $SRC/mysql-server remote add origin https://github.com/mysql/mysql-server.git \
    && git -C $SRC/mysql-server fetch --depth 1 origin 06bcb0eb0ad281e08dd2b4d81b99ad25491433e7 \
    && git -C $SRC/mysql-server checkout FETCH_HEAD
