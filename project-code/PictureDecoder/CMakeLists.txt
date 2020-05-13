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
        DecodingStages/InverseDCTransformer.h
        DecodingStages/AlternateQuantiser.h
        DecodingStages/AlternateIDCT.h
        DecodingStages/MCompensator.h
        DecodingStages/FCTTransformer.h
        DecodingStages/Framestores.h)

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
        DecodingStages/InverseDCTransformer.cpp
        DecodingStages/AlternateQuantiser.cpp
        DecodingStages/AlternateIDCT.cpp
        DecodingStages/MCompensator.cpp
        DecodingStages/FCTTransformer.cpp
        DecodingStages/ForeignIDCT.cpp
        DecodingStages/Framestores.cpp)

add_library(PictureDecoder STATIC ${SOURCE_FILES} ${HEADER_FILES})

#adding profiler required debug info
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -gstabs+")