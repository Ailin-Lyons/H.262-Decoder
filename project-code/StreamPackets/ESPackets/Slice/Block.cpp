//
// Created by elnsa on 2020-01-18.
//

#include <cstdio>
#include "Block.h"

Block::Block(Block::initializerStruct init) {
    cc = init.cc;
    dct_dc_size_luminance = init.dct_dc_size_luminance;
    dct_dc_size_chrominance = init.dct_dc_size_chrominance;
    dct_dc_differential = init.dct_dc_differential;
    num_dct_coefficients = init.num_dct_coefficients;
    dct_coefficients = init.dct_coefficients;
//TODO update fields as needed
}

void Block::print() {
    printf("\tBlock: cc %x, lum %x, chr %x, diff %x, numCoef %x, Coef %x\n", cc, dct_dc_size_luminance,
           dct_dc_size_chrominance,
           dct_dc_differential, num_dct_coefficients, dct_coefficients);
//TODO update fields as needed
}

bool Block::operator==(const Block &rhs) const {
    bool eq = cc == rhs.cc &&
              dct_dc_size_luminance == rhs.dct_dc_size_luminance &&
              dct_dc_size_chrominance == rhs.dct_dc_size_chrominance &&
              dct_dc_differential == rhs.dct_dc_differential &&
              num_dct_coefficients == rhs.num_dct_coefficients;
    if (!eq) return eq;
    for (int i = 0; i < num_dct_coefficients; i++) {
        if (dct_coefficients[i] != rhs.dct_coefficients[i]) return false;
    }
    return true; //TODO update fields as needed
}

bool Block::operator!=(const Block &rhs) const {
    return !(rhs == *this);
}
