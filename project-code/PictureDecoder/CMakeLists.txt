project(PictureDecoder)

set(HEADER_FILES
        PictureDecoder.h
        Picture.h
        Slice/Slice.h
        Slice/Macroblock.h
        Slice/MacroblockModes.h
        Slice/MotionVectors.h
        Slice/MotionVector.h
        Slice/Block.h
        Slice/CodedBlockPattern.h
        DecodingStages/InverseScanner.h
        DecodingStages/InverseQuantizer.h
        DecodingStages/InverseDCTransformer.cpp)

set(SOURCE_FILES
        PictureDecoder.cpp
        Picture.cpp
        Slice/Slice.cpp
        Slice/Macroblock.cpp
        Slice/MacroblockModes.cpp
        Slice/MotionVectors.cpp
        Slice/MotionVector.cpp
        Slice/Block.cpp
        Slice/CodedBlockPattern.cpp
        DecodingStages/InverseScanner.cpp
        DecodingStages/InverseQuantizer.cpp
        DecodingStages/InverseDCTransformer.cpp)

add_library(PictureDecoder STATIC ${SOURCE_FILES} ${HEADER_FILES})