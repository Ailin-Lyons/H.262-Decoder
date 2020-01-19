project(ESPackets)


set(SOURCE_FILES
        PESPacket.cpp
        RegularStartCodes/SequenceExtensionPacket.cpp
        RegularStartCodes/GroupOfPicturesHeaderPacket.cpp PESPacket.cpp
        RegularStartCodes/PictureHeaderPacket.cpp
        RegularStartCodes/SequenceHeaderPacket.cpp
        Slice/SlicePacket.cpp
        RegularStartCodes/SequenceDisplayExtensionPacket.cpp
        RegularStartCodes/PictureCodingExtensionPacket.cpp
        Slice/MacroBlock.cpp)

set(HEADER_FILES
        ESPacket.h
        RegularStartCodes/ExtensionPacket.h
        RegularStartCodes/SequenceExtensionPacket.h
        RegularStartCodes/GroupOfPicturesHeaderPacket.h
        PESPacket.h
        RegularStartCodes/PictureHeaderPacket.h
        RegularStartCodes/SequenceHeaderPacket.h
        Slice/SlicePacket.h
        RegularStartCodes/SequenceDisplayExtensionPacket.h
        RegularStartCodes/PictureCodingExtensionPacket.h
        Slice/MacroBlock.h)

add_library(ESPackets STATIC ${SOURCE_FILES} ${HEADER_FILES})