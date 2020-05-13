cmake_minimum_required(VERSION 3.10)
project(project-code)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES Decoder.cpp)

add_executable(decoder ${SOURCE_FILES})
add_subdirectory(AllTests)

## note - change the display flag to 1 if you want to use Cimg display
#
#set(DISPLAY_FLAG 0)

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

##adding Cimg
#if (DISPLAY_FLAG)
#    find_package(X11 REQUIRED)
#    include_directories(${X11_INCLUDE_DIRS})
#    target_link_libraries(decoder ${X11_LIBRARIES})
#    target_compile_definitions(decoder PRIVATE cimg_use_xrandr=1)
#else()
#    target_compile_definitions(decoder PRIVATE cimg_display=0)
#endif()
#find_package(PNG REQUIRED)
#include_directories(${PNG_INCLUDE_DIRS})
#target_link_libraries(decoder ${PNG_LIBRARIES})
#target_compile_definitions(decoder PRIVATE cimg_use_png=1)
#target_compile_definitions(decoder PRIVATE cimg_use_=4)

#adding pthreads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(decoder Threads::Threads)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#adding profiler required debug info
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -gstabs+")

set(CMAKE_BUILD_TYPE Release)
