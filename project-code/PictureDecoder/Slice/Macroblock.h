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

/**
 * This class represents macroblock() from H262 6.2.5
 */
class Macroblock {
private:
    size_t macroblock_address{}; //This field is used in the motion compensation phase
    size_t macroblock_address_increment;
    MacroblockModes *macroBlockModes;
    unsigned char quantiser_scale_code;
    MotionVectors *forwardMotionVectors;
    MotionVectors *backwardMotionVectors;
    CodedBlockPattern *codedBlockPattern;
    unsigned char block_count;
    Block **blocks;

public:
    struct initializerStruct {
        size_t macroblock_address_increment;
        MacroblockModes *macroBlockModes;
        unsigned char quantiser_scale_code;
        MotionVectors *forwardMotionVectors;
        MotionVectors *backwardMotionVectors;
        CodedBlockPattern *codedBlockPattern;
        unsigned char block_count;
        Block **blocks;
    };

    explicit Macroblock(initializerStruct init);

    ~Macroblock();

    void print();

    bool operator==(const Macroblock &rhs) const;

    bool operator!=(const Macroblock &rhs) const;

    void setBlockCount(unsigned char blockCount);

    void setBlocks(Block **blocks);

    unsigned char getBlockCount() const;

    Block **getBlocks() const;

    unsigned char getQuantiserScaleCode() const;

    MacroblockModes *getMacroBlockModes() const;

    MotionVectors *getForwardMotionVectors() const;

    void setForwardMotionVectors(MotionVectors *forwardMotionVectors);

    MotionVectors *getBackwardMotionVectors() const;

    void setBackwardMotionVectors(MotionVectors *backwardMotionVectors);

    size_t getMacroblockAddressIncrement() const;

    CodedBlockPattern *getCodedBlockPattern() const;

    size_t getMacroblockAddress() const;

    void setMacroblockAddress(size_t macroblockAddress);
};


#endif //PROJECT_CODE_MACROBLOCK_H
