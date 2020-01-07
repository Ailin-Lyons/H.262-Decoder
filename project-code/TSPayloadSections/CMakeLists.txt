project(TSPayloadSections)

set(SOURCE_FILES
        ProgramAssosciationSection.cpp
        ProgramMapSection.cpp)

set(HEADER_FILES
        TSPayloadSections.h
        ProgramAssosciationSection.h
        ProgramMapSection.h
        Descriptor.h)

add_library(TSPayloadSections ${SOURCE_FILES} ${HEADER_FILES})