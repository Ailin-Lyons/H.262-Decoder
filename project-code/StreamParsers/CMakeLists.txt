project(StreamParsers)

set(SOURCE_FILES
        TransportStreamParsers/AFParser.cpp
        TransportStreamParsers/TSParser.cpp
        PacketException.cpp
        ESParser.cpp
        TransportStreamParsers/PESParser.cpp
        TransportStreamParsers/PASParser.cpp
        TransportStreamParsers/PMSParser.cpp
        ESPacketParsers/SequenceHeaderParser.cpp
        ESPacketParsers/GroupHeaderParser.cpp
        ESPacketParsers/PictureHeaderParser.cpp
        ESPacketParsers/SequenceExtensionParser.cpp
        SliceParsers/SliceParser.cpp
        ESPacketParsers/SequenceDisplayExtensionParser.cpp
        ESPacketParsers/PictureCodingExtensionParser.cpp
        ESPacketParsers/MacroBlockParser.cpp
        SliceParsers/BlockParser.cpp
        SliceParsers/CodedBlockPatternParser.cpp
        SliceParsers/MacroblockModesParser.cpp
        SliceParsers/MacroblockParser.cpp
        SliceParsers/MotionVectorParser.cpp
        SliceParsers/MotionVectorsParser.cpp)

set(HEADER_FILES
        SliceParsers/MacroblockParser.h
        SliceParsers/MacroblockModesParser.h
        SliceParsers/MotionVectorParser.h
        ESParser.h)

add_library(StreamParsers STATIC ${SOURCE_FILES} ${HEADER_FILES})