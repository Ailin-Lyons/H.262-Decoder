cmake_minimum_required(VERSION 3.14)
project(project-code)

set(CMAKE_CXX_STANDARD 14)


set(SOURCE_FILES
        Decoder.cpp)

add_executable(decoder ${SOURCE_FILES})


#TODO - adding AllTests
add_subdirectory(AllTests)


# adding the PacketParsersTest
include_directories("PacketParsers")
add_subdirectory("PacketParsers")
target_link_libraries(decoder "PacketParsers")

# adding the TransportPacketStructure
include_directories("TransportPacketStructure")
add_subdirectory("TransportPacketStructure")
target_link_libraries(decoder "TransportPacket")

# adding the TSPayloadSections
include_directories("TSPayloadSections")
add_subdirectory("TSPayloadSections")
target_link_libraries(decoder "TSPayloadSections")

# adding the ESPackets
include_directories("ESPackets")
add_subdirectory("ESPackets")
target_link_libraries(decoder "ESPackets")

# adding the Util
include_directories(Util)
add_subdirectory(Util)
target_link_libraries(decoder Util)
