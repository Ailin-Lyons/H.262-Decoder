project(VideoDecoder)

set(HEADER_FILES
        VideoInformation.h
        VideoDecoder.h)

set(SOURCE_FILES
        VideoException.cpp
        VideoInformation.cpp
        VideoDecoder.cpp)

add_library(VideoDecoder STATIC ${SOURCE_FILES} ${HEADER_FILES})