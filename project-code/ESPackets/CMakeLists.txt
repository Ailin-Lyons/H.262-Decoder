project(ESPackets)


set(SOURCE_FILES
        PESPacket.cpp RegularStartCodes/SequenceExtensionPacket.cpp RegularStartCodes/GroupOfPicturesHeaderPacket.cpp PESPacket.cpp RegularStartCodes/PictureHeaderPacket.cpp RegularStartCodes/SequenceHeaderPacket.cpp RegularStartCodes/SlicePacket.cpp)

set(HEADER_FILES
        ESPacket.h RegularStartCodes/SequenceExtensionPacket.h RegularStartCodes/GroupOfPicturesHeaderPacket.h PESPacket.h RegularStartCodes/PictureHeaderPacket.h RegularStartCodes/SequenceHeaderPacket.h RegularStartCodes/SlicePacket.h)

add_library(ESPackets STATIC ${SOURCE_FILES} ${HEADER_FILES})