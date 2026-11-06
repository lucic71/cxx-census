FROM census-base

RUN apt-get update && apt-get install -y --no-install-recommends libzmq3-dev libsqlite3-dev libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git init $SRC/behaviortree.cpp \
    && git -C $SRC/behaviortree.cpp remote add origin https://github.com/BehaviorTree/BehaviorTree.CPP.git \
    && git -C $SRC/behaviortree.cpp fetch --depth 1 origin a9d6e5637f4a4fcd29fcd16b8db049de7c42006b \
    && git -C $SRC/behaviortree.cpp checkout FETCH_HEAD
