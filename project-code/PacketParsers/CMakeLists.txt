project(PacketParsers)

set(SOURCE_FILES
        AFParser.cpp
        TSParser.cpp
        PESParser.cpp)

add_library(PacketParsers STATIC ${SOURCE_FILES})