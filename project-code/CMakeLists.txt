cmake_minimum_required(VERSION 3.14)
project(project-code)

set(CMAKE_CXX_STANDARD 14)


set(SOURCE_FILES Decoder.cpp)

add_executable(decoder ${SOURCE_FILES})

add_subdirectory(AllTests)


# adding the PacketParsersTest
include_directories("StreamParsers")
add_subdirectory("StreamParsers")
target_link_libraries(decoder "StreamParsers")

# adding the TSPackets
include_directories("TransportPacketStructure")
add_subdirectory("StreamPackets/TSPackets")
target_link_libraries(decoder "TransportPacket")

# adding the TSPayloadSections
include_directories("TSPayloadSections")
add_subdirectory("StreamPackets/TSPayloadSections")
target_link_libraries(decoder "TSPayloadSections")

# adding the ESPackets
include_directories("ESPackets")
add_subdirectory("StreamPackets/ESPackets")
target_link_libraries(decoder "ESPackets")

# adding the Util
include_directories("Util")
add_subdirectory("Util")
target_link_libraries(decoder "Util")

#adding VideoDecoder
include_directories("VideoDecoder")
add_subdirectory("VideoDecoder")
target_link_libraries(decoder "VideoDecoder")

#adding PictureDecoder
include_directories("PictureDecoder")
add_subdirectory("PictureDecoder")
target_link_libraries(decoder "PictureDecoder")
