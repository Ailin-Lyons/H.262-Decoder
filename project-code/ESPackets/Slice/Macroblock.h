//
// Created by bhave on 1/18/2020.
//

#ifndef PROJECT_CODE_MACROBLOCK_H
#define PROJECT_CODE_MACROBLOCK_H


#include "MacroblockModes.h"
#include "MotionVectors.h"
#include "Block.h"

class Macroblock {
private:
    unsigned short macroblock_increment;
    MacroblockModes macroBlockModes;
    unsigned char quantiser_scale_code;
    MotionVectors forwardMotionVectors;
    MotionVectors backwardMotionVectors;
    unsigned short codedBlockPattern;
    Block* blocks;
};


#endif //PROJECT_CODE_MACROBLOCK_H
