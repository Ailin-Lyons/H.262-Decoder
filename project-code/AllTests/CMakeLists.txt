cmake_minimum_required(VERSION 3.10)

project(AllTests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_FILES
        UtilTest/BitManipulatorTest.cpp
        PacketParsersTest/AFParserTest.cpp
        PacketParsersTest/TSParserTest.cpp
        PacketParsersTest/PASPMSParserTest.cpp
        PacketParsersTest/ESParserTest.cpp
        PacketParsersTest/PESParserTest.cpp
        PacketParsersTest/ESPacketParserTest/GroupParserTest.cpp
        PacketParsersTest/ESPacketParserTest/PCExtensionParserTest.cpp
        PacketParsersTest/ESPacketParserTest/PictureHeaderParserTest.cpp
        PacketParsersTest/ESPacketParserTest/SDExtensionParserTest.cpp
        PacketParsersTest/ESPacketParserTest/SeqExtensionParserTest.cpp
        PacketParsersTest/ESPacketParserTest/SeqHeaderParserTest.cpp
        PacketParsersTest/ESPacketParserTest/SliceParserTest.cpp
        PictureDecoderTest/InverseScannerTest.cpp PictureDecoderTest/IDCTest.cpp PictureDecoderTest/AllFramesTest.cpp)

add_executable(AllTests ${TEST_FILES})

#add_compile_options(gtest_disable_pthreads)

#include_directories(../Util)

add_dependencies(AllTests Util)
add_dependencies(AllTests TransportPacket)
add_dependencies(AllTests StreamParsers)
add_dependencies(AllTests ESPackets)
add_dependencies(AllTests TSPayloadSections)

target_link_libraries(AllTests gtest gtest_main)
target_link_libraries(AllTests Util)
target_link_libraries(AllTests TransportPacket)
target_link_libraries(AllTests StreamParsers)
target_link_libraries(AllTests ESPackets)
target_link_libraries(AllTests TSPayloadSections)
target_link_libraries(AllTests VideoDecoder)
target_link_libraries(AllTests PictureDecoder)

#adding pthreads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(AllTests Threads::Threads)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")