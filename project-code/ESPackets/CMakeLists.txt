project(PesPacket)

project(TSPacket)

set(SOURCE_FILES
        PESPacket.cpp ExtensionPayload.cpp GroupPayload.cpp PESPacket.cpp PicturePayload.cpp SequenceHeaderPayload.cpp SlicePayload.cpp VideoPayload.cpp)

set(HEADER_FILES
        ESPacket.h ExtensionPayload.h GroupPayload.h PESPacket.h PicturePayload.h SequenceHeaderPayload.h SlicePayload.h VideoPayload.h)

add_library(ESPackets STATIC ${SOURCE_FILES} ${HEADER_FILES})