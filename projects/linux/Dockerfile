FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      bc bison flex cpio kmod libelf-dev libssl-dev python3 rsync \
    && rm -rf /var/lib/apt/lists/*

# The kernel tree is bind-mounted read-only at $SRC/linux (see build.sh).
