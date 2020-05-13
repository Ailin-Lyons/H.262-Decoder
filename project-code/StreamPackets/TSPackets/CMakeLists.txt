project(TransportPacket)

set(SOURCE_FILES
        AdaptationField.cpp
        TransportPacket.cpp)

set(HEADER_FILES
        AdaptationField.h
        TransportPacket.h)

add_library(TransportPacket STATIC ${SOURCE_FILES} ${HEADER_FILES})

#adding profiler required debug info
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -gstabs+")