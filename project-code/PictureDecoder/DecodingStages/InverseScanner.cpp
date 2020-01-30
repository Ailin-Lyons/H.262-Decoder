//
// Created by elnsa on 2020-01-29.
//

#include "InverseScanner.h"
#include "../VideoDecoder/VideoException.cpp"

char InverseScanner::scan_0[8][8] = {{0,  1,  5,  6, 14,  15, 27, 28},
                                     {2,  4,  7,  13, 16, 26, 29, 42},
                                     {3,  8,  12, 17, 25, 30, 41, 43},
                                     {9,  11, 18, 24, 31, 40, 44, 53},
                                     {10, 19, 23, 32, 39, 45, 52, 54},
                                     {20, 22, 33, 38, 46, 51, 55, 60},
                                     {21, 34, 37, 47, 50, 56, 59, 61},
                                     {35, 36, 48, 49, 57, 58, 62, 63}};


void InverseScanner::performInverseScan(HPicture *picture, bool alternate_scan) {
    if (picture->getState() != HPicture::decoding_state::variable_length_decoded)
        throw VideoException("InverseScanner: received picture in incorrect state.\n");
    if (alternate_scan) throw VideoException("InverseScanner: alternate_scan is not handled by this decoder");
    for (size_t s = 0; s < picture->getNumSlices(); s++) {
        Slice *slice = picture->getSlices()[s];
        for (size_t m = 0; m < slice->getNumMacroblocks(); m++) {
            Macroblock *macroblock = &slice->getMacroblocks()[m];
            for (size_t b = 0; b < macroblock->getBlockCount(); b++) {
                Block *block = macroblock->getBlocks()[b];
                if (block) performInverseScanHelper(block);
            }
        }
    }
    picture->setState(HPicture::decoding_state::inverse_scanned);
}

void InverseScanner::performInverseScanHelper(Block *block) {
    int *qf = (int *) malloc(sizeof(int) * 8 * 8);
    for (size_t v = 0; v < 8; v++) {
        for (size_t u = 0; u < 8; u++) {
            qf[v * 8 + u] = block->getQfs()[scan_0[v][u]];
        }
    }
    block->setQFscanned(qf);
}
