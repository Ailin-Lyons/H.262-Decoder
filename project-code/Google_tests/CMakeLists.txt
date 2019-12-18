project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


# adding the Google_Tests_run target
add_executable(Google_Tests_run Test1.cpp)

# linking Google_Tests_run with the correct test target which will be tested
#target_link_libraries(Google_Tests_run PacketParsers)
# TODO - this is broken because the gtest target is not properly set

target_link_libraries(Google_Tests_run gtest gtest_main)