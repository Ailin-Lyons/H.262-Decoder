//
// Created by bhave on 1/18/2020.
//

#include <cstdio>
#include "Macroblock.h"

Macroblock::Macroblock(Macroblock::initializerStruct init) {
    macroblock_address_increment = init.macroblock_address_increment;
    macroBlockModes = init.macroBlockModes;
    quantiser_scale_code = init.quantiser_scale_code;
    forwardMotionVectors = init.forwardMotionVectors;
    backwardMotionVectors = init.backwardMotionVectors;
    codedBlockPattern = init.codedBlockPattern;
    numBlocks = init.numBlocks;
    blocks = init.blocks;
}

void Macroblock::print() {
    printf("\tMacroblock: mai = %x, qsc = %x, numBlocks = %x\n", macroblock_address_increment, quantiser_scale_code,
           numBlocks);
    macroBlockModes->print();
    if (forwardMotionVectors != nullptr) {
        printf("\tForward:");
        forwardMotionVectors->print();
    }
    if (backwardMotionVectors != nullptr) {
        printf("\tBackward:");
        backwardMotionVectors->print();
    }
    if (codedBlockPattern != nullptr) {
        codedBlockPattern->print();
    }
//    for(size_t i = 0; i < numBlocks; i++){  //TODO uncomment this when block is made
//        blocks[i].print();
//    }
}

bool Macroblock::operator==(const Macroblock &rhs) const {
    bool eq = macroblock_address_increment == rhs.macroblock_address_increment &&
              *macroBlockModes == *rhs.macroBlockModes &&
              quantiser_scale_code == rhs.quantiser_scale_code &&
              *forwardMotionVectors == *rhs.forwardMotionVectors &&
              *backwardMotionVectors == *rhs.backwardMotionVectors &&
              *codedBlockPattern == *rhs.codedBlockPattern &&
              numBlocks == rhs.numBlocks;
    if (!eq) return eq;
//    for (size_t i = 0; i < numBlocks; i++) { //TODO uncomment this when block is made
//        if (blocks[i] != rhs.blocks[i]) {
//            return false;
//        }
//    }
    return true;
}

bool Macroblock::operator!=(const Macroblock &rhs) const {
    return !(rhs == *this);
}
