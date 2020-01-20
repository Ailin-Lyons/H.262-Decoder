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
    blocks = init.blocks;
}

void Macroblock::print() {
    printf("TODO macroblock::print\n");
//TODO
}

bool Macroblock::operator==(const Macroblock &rhs) const {
    return false;//TODO
}

bool Macroblock::operator!=(const Macroblock &rhs) const {
    return !(rhs == *this);
}
