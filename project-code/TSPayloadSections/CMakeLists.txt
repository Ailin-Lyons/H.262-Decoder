project(TSPayloadSections)

set(SOURCE_FILES
        ProgramAssociationSection.cpp
        ProgramMapSection.cpp)

set(HEADER_FILES
        TSPayloadSections.h
        ProgramAssociationSection.h
        ProgramMapSection.h
        Descriptor.h)

add_library(TSPayloadSections ${SOURCE_FILES} ${HEADER_FILES})