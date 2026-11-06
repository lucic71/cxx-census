FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends \
      libtbb-dev libpugixml-dev ocl-icd-opencl-dev opencl-headers rapidjson-dev libva-dev \
      libsnappy-dev python3-dev python3-pip python3-venv pybind11-dev libffi-dev nlohmann-json3-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/openvino \
    && git -C $SRC/openvino remote add origin https://github.com/openvinotoolkit/openvino.git \
    && git -C $SRC/openvino fetch --depth 1 origin 92096e1c255cbd816480be7e4ead89da3f0189d8 \
    && git -C $SRC/openvino checkout FETCH_HEAD \
    && git -C $SRC/openvino submodule update --init --recursive --depth 1
