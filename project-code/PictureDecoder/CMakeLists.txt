project(PictureDecoder)

set(HEADER_FILES
        PictureDecoder.h)

set(SOURCE_FILES
        PictureDecoder.cpp)

add_library(PictureDecoder STATIC ${SOURCE_FILES} ${HEADER_FILES})