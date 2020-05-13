project(Util)

set(HEADER_FILES
        FileInterface.h)

set(SOURCE_FILES
        BitManipulator.cpp
        FileInterface.cpp
        FileException.cpp)

add_library(Util STATIC ${SOURCE_FILES} ${HEADER_FILES})

#adding profiler required debug info
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -gstabs+")