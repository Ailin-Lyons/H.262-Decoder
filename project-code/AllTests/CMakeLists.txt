cmake_minimum_required(VERSION 3.14)

project(AllTests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


set(UTIL_TEST_FILES
        UtilTest/BitManipulatorTest.cpp)

#TODO - include other test files as well
set(OTHER_TEST_FILES
        DecoderTest.cpp)

add_executable(AllTests ${UTIL_TEST_FILES})
target_link_libraries(AllTests Util)
target_link_libraries(AllTests gtest gtest_main)