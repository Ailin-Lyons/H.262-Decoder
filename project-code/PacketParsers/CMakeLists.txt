project(PacketParsers)

set(SOURCE_FILES
        AFParser.cpp
        TSParser.cpp
        )

add_library(PacketParsers STATIC ${SOURCE_FILES})