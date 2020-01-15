project(ESPackets)


set(SOURCE_FILES
        PESPacket.cpp RegularStartCodes/ExtensionPacket.cpp RegularStartCodes/GroupPacket.cpp PESPacket.cpp RegularStartCodes/PicturePacket.cpp RegularStartCodes/SequenceHeaderPacket.cpp RegularStartCodes/SlicePacket.cpp)

set(HEADER_FILES
        ESPacket.h RegularStartCodes/ExtensionPacket.h RegularStartCodes/GroupPacket.h PESPacket.h RegularStartCodes/PicturePacket.h RegularStartCodes/SequenceHeaderPacket.h RegularStartCodes/SlicePacket.h)

add_library(ESPackets STATIC ${SOURCE_FILES} ${HEADER_FILES})