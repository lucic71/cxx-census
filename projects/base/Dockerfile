FROM ubuntu:24.04

ARG CLANG_VERSION=23

RUN apt-get update && apt-get install -y --no-install-recommends \
      build-essential ca-certificates cmake git ninja-build pkg-config wget \
    && rm -rf /var/lib/apt/lists/*

RUN wget -qO /etc/apt/trusted.gpg.d/apt.llvm.org.asc https://apt.llvm.org/llvm-snapshot.gpg.key \
    && echo "deb http://apt.llvm.org/noble/ llvm-toolchain-noble-${CLANG_VERSION} main" \
         > /etc/apt/sources.list.d/llvm.list \
    && apt-get update && apt-get install -y --no-install-recommends \
         clang-${CLANG_VERSION} libclang-${CLANG_VERSION}-dev llvm-${CLANG_VERSION}-dev \
    && rm -rf /var/lib/apt/lists/*

ENV CLANG_VERSION=${CLANG_VERSION}
ENV CC=clang-${CLANG_VERSION}
ENV CXX=clang++-${CLANG_VERSION}

ENV SRC=/src
ENV BUILD=/build
WORKDIR $SRC
