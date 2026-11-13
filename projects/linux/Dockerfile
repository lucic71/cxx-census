FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      bc bison flex cpio kmod libelf-dev libssl-dev python3 rsync \
    && rm -rf /var/lib/apt/lists/*
