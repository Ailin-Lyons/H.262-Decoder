//
// Created by bhave on 1/18/2020.
//

#ifndef PROJECT_CODE_MACROBLOCK_H
#define PROJECT_CODE_MACROBLOCK_H


#include "MacroblockModes.h"
#include "MotionVectors.h"
#include "Block.h"
#include "CodedBlockPattern.h"
#include <cstddef>

class Macroblock {
private:
    size_t macroblock_address_increment;
    MacroblockModes *macroBlockModes;
    unsigned char quantiser_scale_code;
    MotionVectors *forwardMotionVectors;
    MotionVectors *backwardMotionVectors;
    CodedBlockPattern *codedBlockPattern;
    unsigned char block_count;
    Block *blocks;
public:
    struct initializerStruct {
        size_t macroblock_address_increment;
        MacroblockModes *macroBlockModes;
        unsigned char quantiser_scale_code;
        MotionVectors *forwardMotionVectors;
        MotionVectors *backwardMotionVectors;
        CodedBlockPattern *codedBlockPattern;
        unsigned char block_count;
        Block *blocks;
    };

    Macroblock(initializerStruct init);

    ~Macroblock() = default; //TODO make a destructor

    void print();

    bool operator==(const Macroblock &rhs) const;

    bool operator!=(const Macroblock &rhs) const;
};


#endif //PROJECT_CODE_MACROBLOCK_H
