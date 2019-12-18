project(PesPacket)

project(TSPacket)

set(SOURCE_FILES
        PesPacket.cpp)

set(HEADER_FILES
        PesPacket.h)

add_library(PesPacket STATIC ${SOURCE_FILES} ${HEADER_FILES})