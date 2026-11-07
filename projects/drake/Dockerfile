FROM census-base

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      gfortran libblas-dev libeigen3-dev libgl-dev libglib2.0-dev libglx-dev liblapack-dev \
      libopengl-dev libspdlog-dev lld ocl-icd-opencl-dev opencl-headers patch python3-all-dev \
      python3-matplotlib python3-numpy python3-pil python3-pydot python3-yaml zlib1g-dev \
      libegl1 libgomp1 libx11-6 libomp-23-dev locales unzip zip curl \
    && locale-gen en_US.UTF-8 && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/drake \
    && git -C $SRC/drake remote add origin https://github.com/RobotLocomotion/drake.git \
    && git -C $SRC/drake fetch --depth 1 origin 1610676d38df7854153cd04e1ba32e286fd617b1 \
    && git -C $SRC/drake checkout FETCH_HEAD
