cmake_minimum_required(VERSION 3.14)

project(AllTests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


set(TEST_FILES
        UtilTest/BitManipulatorTest.cpp)

add_executable(AllTests ${TEST_FILES})
#target_link_libraries(AllTests Util)
target_link_libraries(AllTests gtest gtest_main)