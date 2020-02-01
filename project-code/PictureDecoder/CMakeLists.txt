project(PictureDecoder)

set(HEADER_FILES
        PictureDecoder.h
        HPicture.h
        Slice/Slice.h
        Slice/Macroblock.h
        Slice/MacroblockModes.h
        Slice/MotionVectors.h
        Slice/MotionVector.h
        Slice/Block.h
        Slice/CodedBlockPattern.h
        DecodingStages/InverseScanner.h
        DecodingStages/InverseQuantiser.h
        DecodingStages/InverseDCTransformer.h)

set(SOURCE_FILES
        PictureDecoder.cpp
        HPicture.cpp
        Slice/Slice.cpp
        Slice/Macroblock.cpp
        Slice/MacroblockModes.cpp
        Slice/MotionVectors.cpp
        Slice/MotionVector.cpp
        Slice/Block.cpp
        Slice/CodedBlockPattern.cpp
        DecodingStages/InverseScanner.cpp
        DecodingStages/InverseQuantiser.cpp
        DecodingStages/InverseDCTransformer.cpp)

add_library(PictureDecoder STATIC ${SOURCE_FILES} ${HEADER_FILES})