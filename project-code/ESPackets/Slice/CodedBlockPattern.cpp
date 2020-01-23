//
// Created by elnsa on 2020-01-19.
//

#include <cstdio>
#include "CodedBlockPattern.h"

CodedBlockPattern::CodedBlockPattern(CodedBlockPattern::initializerStruct init) {
    coded_block_pattern_420 = init.coded_block_pattern_420;
    coded_block_pattern_1 = init.coded_block_pattern_1;
    coded_block_pattern_2 = init.coded_block_pattern_2;
}

void CodedBlockPattern::print() {
    printf("cf420 %x, cfp1 %x, cfp2 %x\n", coded_block_pattern_420, coded_block_pattern_1, coded_block_pattern_2);
}

bool CodedBlockPattern::operator==(const CodedBlockPattern &rhs) const {
    return coded_block_pattern_420 == rhs.coded_block_pattern_420 &&
           coded_block_pattern_1 == rhs.coded_block_pattern_1 &&
           coded_block_pattern_2 == rhs.coded_block_pattern_2;
}

bool CodedBlockPattern::operator!=(const CodedBlockPattern &rhs) const {
    return !(rhs == *this);
}
