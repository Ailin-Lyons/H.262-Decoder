cmake_minimum_required(VERSION 3.14)

project(AllTests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_FILES
        UtilTest/BitManipulatorTest.cpp PacketParsersTest/AFParserTest.cpp PacketParsersTest/TSParserTest.cpp PacketParsersTest/PASParserTest.cpp)

add_executable(AllTests ${TEST_FILES})

#add_compile_options(gtest_disable_pthreads)

#include_directories(../Util)

add_dependencies(AllTests Util)
add_dependencies(AllTests TransportPacket)
add_dependencies(AllTests PacketParsers)
add_dependencies(AllTests TSPayloadSections)

target_link_libraries(AllTests Util)
target_link_libraries(AllTests gtest gtest_main)
target_link_libraries(AllTests PacketParsers)
target_link_libraries(AllTests TransportPacket)
target_link_libraries(AllTests TSPayloadSections)
