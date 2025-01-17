//
// Created by bhave on 1/18/2020.
//

#include <cstdio>
#include <cstdlib>
#include "Macroblock.h"

Macroblock::Macroblock(Macroblock::initializerStruct init) {
    macroblock_address_increment = init.macroblock_address_increment;
    macroBlockModes = init.macroBlockModes;
    quantiser_scale_code = init.quantiser_scale_code;
    forwardMotionVectors = init.forwardMotionVectors;
    backwardMotionVectors = init.backwardMotionVectors;
    codedBlockPattern = init.codedBlockPattern;
    block_count = init.block_count;
    blocks = init.blocks;
}

void Macroblock::print() {
    printf("\tMacroblock: mai = %x, qsc = %x, block_count = %x\n", (int) macroblock_address_increment,
           quantiser_scale_code,
           block_count);
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
    if (blocks) {
        for (size_t i = 0; i < block_count; i++) {
            if (blocks[i] != nullptr) blocks[i]->print();
        }
    }
}

bool Macroblock::operator==(const Macroblock &rhs) const {
    bool eq = macroblock_address_increment == rhs.macroblock_address_increment &&
              *macroBlockModes == *rhs.macroBlockModes &&
              quantiser_scale_code == rhs.quantiser_scale_code &&
              *forwardMotionVectors == *rhs.forwardMotionVectors &&
              *backwardMotionVectors == *rhs.backwardMotionVectors &&
              *codedBlockPattern == *rhs.codedBlockPattern &&
              block_count == rhs.block_count;
    if (!eq) return eq;
    for (size_t i = 0; i < block_count; i++) {
        if (blocks[i] != rhs.blocks[i]) {
            return false;
        }
    }
    return true;
}

bool Macroblock::operator!=(const Macroblock &rhs) const {
    return !(rhs == *this);
}

Macroblock::~Macroblock() {
    delete macroBlockModes;
    delete forwardMotionVectors;
    delete backwardMotionVectors;
    delete codedBlockPattern;
    if (blocks) {
        for (int i = 0; i < block_count; i++) {
            if (blocks[i]) delete (blocks[i]);
        }
        free(blocks);
    }

}

unsigned char Macroblock::getBlockCount() const {
    return block_count;
}

void Macroblock::setBlockCount(unsigned char blockCount) {
    block_count = blockCount;
}

Block **Macroblock::getBlocks() const {
    return blocks;
}

void Macroblock::setBlocks(Block **blocks) {
    Macroblock::blocks = blocks;
}

unsigned char Macroblock::getQuantiserScaleCode() const {
    return quantiser_scale_code;
}

MacroblockModes *Macroblock::getMacroBlockModes() const {
    return macroBlockModes;
}

MotionVectors *Macroblock::getForwardMotionVectors() const {
    return forwardMotionVectors;
}

void Macroblock::setForwardMotionVectors(MotionVectors *forwardMotionVectors) {
    Macroblock::forwardMotionVectors = forwardMotionVectors;
}

MotionVectors *Macroblock::getBackwardMotionVectors() const {
    return backwardMotionVectors;
}

void Macroblock::setBackwardMotionVectors(MotionVectors *backwardMotionVectors) {
    Macroblock::backwardMotionVectors = backwardMotionVectors;
}

size_t Macroblock::getMacroblockAddressIncrement() const {
    return macroblock_address_increment;
}

CodedBlockPattern *Macroblock::getCodedBlockPattern() const {
    return codedBlockPattern;
}

size_t Macroblock::getMacroblockAddress() const {
    return macroblock_address;
}

void Macroblock::setMacroblockAddress(size_t macroblockAddress) {
    macroblock_address = macroblockAddress;
}

void Macroblock::setBlock(size_t index, Block *block) {
    if (blocks) {
        blocks[index] = block;
    }
}

Block *Macroblock::getBlock(size_t index) const {
    if (blocks) {
        return blocks[index];
    }
    return nullptr;
}
