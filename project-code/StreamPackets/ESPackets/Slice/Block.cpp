//
// Created by elnsa on 2020-01-18.
//

#include <cstdio>
#include <cstdlib>
#include "Block.h"

Block::Block(Block::initializerStruct init) {
    cc = init.cc;
    dct_dc_size = init.dct_dc_size;
    dct_dc_differential = init.dct_dc_differential;
    QFS = init.QFS;
}

void Block::print() {
    printf("\tBlock: cc %x, dc_sc_size = %x, diff %x\n", cc, dct_dc_size,
           dct_dc_differential);
    for (int i = 0; i < 8; i++) {
        printf("\t\t");
        for (int j = 0; j < 8; j++) {
            printf("%i ", QFS[8 * i + j]);
        }
        printf("\n");
    }
}

bool Block::operator==(const Block &rhs) const {
    bool eq = cc == rhs.cc &&
              dct_dc_size == rhs.dct_dc_size &&
              dct_dc_differential == rhs.dct_dc_differential;
    if (!eq) return eq;
    for (int i = 0; i < 64; i++) {
        if (QFS[i] != rhs.QFS[i]) return false;
    }
    return true;
}

bool Block::operator!=(const Block &rhs) const {
    return !(rhs == *this);
}

Block::~Block() {
    free(QFS);
}
