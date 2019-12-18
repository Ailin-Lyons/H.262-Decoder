cmake_minimum_required(VERSION 3.14)
project(project-code)

set(CMAKE_CXX_STANDARD 14)


set(SOURCE_FILES
        Decoder.cpp
        Util/BitManipulator.cpp)

add_executable(decoder ${SOURCE_FILES})


#TODO - adding AllTests
add_subdirectory(AllTests)


# adding the PacketParsers
include_directories("PacketParsers")
add_subdirectory("PacketParsers")
target_link_libraries(decoder "PacketParsers")

# adding the TransportPacketStructure
include_directories("TransportPacketStructure")
add_subdirectory("TransportPacketStructure")
target_link_libraries(decoder "TSPacket")

# adding the PesPacket
include_directories("PesPacket")
add_subdirectory("PesPacket")
target_link_libraries(decoder "PesPacket")

# adding the Util
include_directories(Util)
add_subdirectory(Util)
target_link_libraries(decoder Util)
