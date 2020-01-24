//
// Created by elnsa on 2020-01-19.
//

#include <cstdio>
#include "CodedBlockPattern.h"

CodedBlockPattern::CodedBlockPattern(CodedBlockPattern::initializerStruct init) {
    cbp = init.cbp;
    coded_block_pattern_1 = init.coded_block_pattern_1;
    coded_block_pattern_2 = init.coded_block_pattern_2;
}

void CodedBlockPattern::print() {
    printf("\tCodedBlockPattern:cf420 %x, cfp1 %x, cfp2 %x\n", cbp, coded_block_pattern_1, coded_block_pattern_2);
}

bool CodedBlockPattern::operator==(const CodedBlockPattern &rhs) const {
    return cbp == rhs.cbp &&
           coded_block_pattern_1 == rhs.coded_block_pattern_1 &&
           coded_block_pattern_2 == rhs.coded_block_pattern_2;
}

bool CodedBlockPattern::operator!=(const CodedBlockPattern &rhs) const {
    return !(rhs == *this);
}

unsigned char CodedBlockPattern::getCbp() const {
    return cbp;
}

unsigned char CodedBlockPattern::getCodedBlockPattern1() const {
    return coded_block_pattern_1;
}

unsigned char CodedBlockPattern::getCodedBlockPattern2() const {
    return coded_block_pattern_2;
}
