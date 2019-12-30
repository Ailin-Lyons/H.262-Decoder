project(Util)

set(HEADER_FILES
        FileInterface.h)

set(SOURCE_FILES
        BitManipulator.cpp
        FileInterface.cpp
        FileException.cpp InitializationException.cpp)

add_library(Util STATIC ${SOURCE_FILES} ${HEADER_FILES})