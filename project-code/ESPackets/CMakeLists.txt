project(PesPacket)

project(TSPacket)

set(SOURCE_FILES
        PESPacket.cpp)

set(HEADER_FILES
        PESPacket.h ESPacket.h VideoPayload.cpp VideoPayload.h)

add_library(ESPackets STATIC ${SOURCE_FILES} ${HEADER_FILES})