project(TSPayloadPackets)

set(SOURCE_FILES
        ProgramAssosciationSection.cpp
        ProgramMapSection.cpp)

set(HEADER_FILES
        TSPayloadSections.h
        ProgramAssosciationSection.h
        ProgramMapSection.h
        Descriptor.h)

add_library(TSPayloadPackets ${SOURCE_FILES} ${HEADER_FILES})