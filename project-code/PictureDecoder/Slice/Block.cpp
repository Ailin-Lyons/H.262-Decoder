//
// Created by elnsa on 2020-01-18.
//

#include <cstdio>
#include <cstdlib>
#include "Block.h"

Block::Block(Block::initializerStruct init) {
    i = init.i;
    cc = init.cc;
    dct_dc_size = init.dct_dc_size;
    dct_dc_differential = init.dct_dc_differential;
    data = init.QFS;
}

void Block::print() {
    printf("\tBlock[%x]: cc %x, dc_sc_size = %x, diff %x\n", (int) i, cc, dct_dc_size,
           dct_dc_differential);
    if(data!= nullptr){
        for (int i = 0; i < 8; i++) {
            printf("\t\t");
            for (int j = 0; j < 8; j++) {
                printf("%4i ", data[8 * i + j]);
            }
            printf("\n");
        }
    }else{
        printf("no data\n");
    }
}

bool Block::operator==(const Block &rhs) const {
    bool eq = i == rhs.i &&
              cc == rhs.cc &&
              dct_dc_size == rhs.dct_dc_size &&
              dct_dc_differential == rhs.dct_dc_differential;
    if (!eq) return eq;
    for (int i = 0; i < 64; i++) {
        if (data[i] != rhs.data[i]) return false;
    }
    return true;
}

bool Block::operator!=(const Block &rhs) const {
    return !(rhs == *this);
}

Block::~Block() {
    if (data) free(data);
}

int *Block::getData() const {
    return data;
}

void Block::setData(int *block_data) {
    data = block_data;
}

unsigned char Block::getCc() const {
    return cc;
}
