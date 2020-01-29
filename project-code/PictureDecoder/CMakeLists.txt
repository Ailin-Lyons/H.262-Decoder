project(PictureDecoder)

set(HEADER_FILES
        PictureDecoder.h
        Picture.h)

set(SOURCE_FILES
        PictureDecoder.cpp
        Picture.cpp)

add_library(PictureDecoder STATIC ${SOURCE_FILES} ${HEADER_FILES})