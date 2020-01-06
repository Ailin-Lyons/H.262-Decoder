project(PacketParsers)

set(SOURCE_FILES
        AFParser.cpp
        TSParser.cpp
        PacketException.cpp
        ESParser.cpp
        PESParser.cpp
        PASParser.cpp
        PMSParser.cpp)

set(HEADER_FILES
        ESParser.h)

add_library(PacketParsers STATIC ${SOURCE_FILES} ${HEADER_FILES})