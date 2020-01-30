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
    QFS = init.QFS;
}

void Block::print() {
    printf("\tBlock[%x]: cc %x, dc_sc_size = %x, diff %x\n", i, cc, dct_dc_size,
           dct_dc_differential);
    printf("VLC Table:\n");
    for (int i = 0; i < 8; i++) {
        printf("\t\t");
        for (int j = 0; j < 8; j++) {
            printf("%i ", QFS[8 * i + j]);
        }
        printf("\n");
    }
    printf("IS Table:\n");
    for (int i = 0; i < 8; i++) {
        printf("\t\t");
        for (int j = 0; j < 8; j++) {
            printf("%i ", QFscanned[8 * i + j]);
        }
        printf("\n");
    }
}

bool Block::operator==(const Block &rhs) const {
    bool eq = i == rhs.i &&
              cc == rhs.cc &&
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
    if (QFS) free(QFS);
    if (QFscanned) free(QFscanned);
    if (Fquantized) free(Fquantized);
    if (fdctransformed) free(fdctransformed);
}

int *Block::getQfs() const {
    return QFS;
}

void Block::setQfs(int *qfs) {
    QFS = qfs;
}

int *Block::getQFscanned() const {
    return QFscanned;
}

void Block::setQFscanned(int *qFscanned) {
    QFscanned = qFscanned;
}

int *Block::getFquantized() const {
    return Fquantized;
}

void Block::setFquantized(int *fquantized) {
    Fquantized = fquantized;
}

int *Block::getFdctransformed() const {
    return fdctransformed;
}

void Block::setFdctransformed(int *fdctransformed) {
    Block::fdctransformed = fdctransformed;
}
