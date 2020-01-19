project(PacketParsers)

set(SOURCE_FILES
        AFParser.cpp
        TSParser.cpp
        PacketException.cpp
        ESParser.cpp
        PESParser.cpp
        PASParser.cpp
        PMSParser.cpp
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
        ESParser.h)

add_library(PacketParsers STATIC ${SOURCE_FILES} ${HEADER_FILES})