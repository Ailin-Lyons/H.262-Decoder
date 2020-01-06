project(TSPayloadPackets)

set(SOURCE_FILES
        PASPacket.cpp
        PMSPacket.cpp)

set(HEADER_FILES
        TSPayloadPacket.h
        PASPacket.h
        PMSPacket.h)

add_library(TSPayloadPackets ${SOURCE_FILES} ${HEADER_FILES})