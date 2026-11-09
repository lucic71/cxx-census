FROM census-base

RUN git clone https://github.com/facebook/yoga.git $SRC/yoga \
    && git -C $SRC/yoga checkout 41118bd3a86c637fdb43a90fd596e78375137d0f \
    && cd $SRC/yoga/tests \
    && rm YGConfigTest.cpp SmallValueBufferTest.cpp CacheTest.cpp EventPublisherTest.cpp EventsTest.cpp \
          YGFlexBasisFitContentTest.cpp YGHadOverflowTest.cpp YGPersistentNodeCloningTest.cpp
