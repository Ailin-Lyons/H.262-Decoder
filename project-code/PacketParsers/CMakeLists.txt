project(PacketParsers)

set(SOURCE_FILES
        AFParser.cpp
        TSParser.cpp
        PacketException.cpp)

add_library(PacketParsers STATIC ${SOURCE_FILES})