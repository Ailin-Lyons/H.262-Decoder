project(PesPacket)

project(TSPacket)

set(SOURCE_FILES
        PESPacket.cpp)

set(HEADER_FILES
        PESPacket.h PESPayload.h VideoPayload.cpp VideoPayload.h)

add_library(PesPacket STATIC ${SOURCE_FILES} ${HEADER_FILES})