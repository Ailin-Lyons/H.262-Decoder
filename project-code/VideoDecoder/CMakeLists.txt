project(VideoDecoder)

set(HEADER_FILES
        VideoInformation.h
        VideoDecoder.h)

set(SOURCE_FILES
        VideoInformation.cpp
        VideoDecoder.cpp)

add_library(VideoDecoder STATIC ${SOURCE_FILES} ${HEADER_FILES})