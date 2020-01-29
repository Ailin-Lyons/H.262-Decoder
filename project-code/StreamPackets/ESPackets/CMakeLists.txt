project(ESPackets)


set(SOURCE_FILES
        PESPacket.cpp
        RegularStartCodes/SequenceExtensionPacket.cpp
        RegularStartCodes/GroupOfPicturesHeaderPacket.cpp PESPacket.cpp
        RegularStartCodes/PictureHeaderPacket.cpp
        RegularStartCodes/SequenceHeaderPacket.cpp
        Slice/Slice.cpp
        RegularStartCodes/SequenceDisplayExtensionPacket.cpp
        RegularStartCodes/PictureCodingExtensionPacket.cpp
        Slice/Macroblock.cpp
        Slice/MacroblockModes.cpp
        Slice/MotionVectors.cpp
        Slice/MotionVector.cpp
        Slice/Block.cpp
        Slice/CodedBlockPattern.cpp)

set(HEADER_FILES
        ESPacket.h
        RegularStartCodes/ExtensionPacket.h
        RegularStartCodes/SequenceExtensionPacket.h
        RegularStartCodes/GroupOfPicturesHeaderPacket.h
        PESPacket.h
        RegularStartCodes/PictureHeaderPacket.h
        RegularStartCodes/SequenceHeaderPacket.h
        Slice/Slice.h
        RegularStartCodes/SequenceDisplayExtensionPacket.h
        RegularStartCodes/PictureCodingExtensionPacket.h
        Slice/Macroblock.h
        Slice/MacroblockModes.h
        Slice/MotionVectors.h
        Slice/MotionVector.h
        Slice/Block.h
        Slice/CodedBlockPattern.h)

add_library(ESPackets STATIC ${SOURCE_FILES} ${HEADER_FILES})