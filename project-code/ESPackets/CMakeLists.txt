project(PesPacket)

project(TSPacket)

set(SOURCE_FILES
        PESPacket.cpp ExtensionPacket.cpp GroupPacket.cpp PESPacket.cpp PicturePacket.cpp SequenceHeaderPacket.cpp SlicePacket.cpp VideoPayload.cpp)

set(HEADER_FILES
        ESPacket.h ExtensionPacket.h GroupPacket.h PESPacket.h PicturePacket.h SequenceHeaderPacket.h SlicePacket.h VideoPayload.h)

add_library(ESPackets STATIC ${SOURCE_FILES} ${HEADER_FILES})