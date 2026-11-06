FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends libasound2-dev python3 \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/sherpa-onnx \
    && git -C $SRC/sherpa-onnx remote add origin https://github.com/k2-fsa/sherpa-onnx.git \
    && git -C $SRC/sherpa-onnx fetch --depth 1 origin 3e437b331fa273ae0819bc19659eb0f53efc03d3 \
    && git -C $SRC/sherpa-onnx checkout FETCH_HEAD
