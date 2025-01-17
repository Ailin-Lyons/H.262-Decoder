//
// Created by elnsa on 2020-01-29.
//

#include <VideoDecoder.h>
#include "InverseQuantiser.h"
#include "../VideoDecoder/VideoException.cpp"
#include "InverseScanner.h"

#define WEIGHT (generateWeightingValue(u, v, w, intra))
#define Sign(val) ((val) > 0 ? 1 : (((val) == 0) ? 0 : -1))

unsigned char InverseQuantiser::qsc = 0;

InverseQuantiser::quantiserTable InverseQuantiser::conversion_table[] = {{1,  2,  1},
                                                                         {2,  4,  2},
                                                                         {3,  6,  3},
                                                                         {4,  8,  4},
                                                                         {5,  10, 5},
                                                                         {6,  12, 6},
                                                                         {7,  14, 7},
                                                                         {8,  16, 8},
                                                                         {9,  18, 10},
                                                                         {10, 20, 12},
                                                                         {11, 22, 14},
                                                                         {12, 24, 16},
                                                                         {13, 26, 18},
                                                                         {14, 28, 20},
                                                                         {15, 30, 22},
                                                                         {16, 32, 24},
                                                                         {17, 34, 28},
                                                                         {18, 36, 32},
                                                                         {19, 38, 36},
                                                                         {20, 40, 40},
                                                                         {21, 42, 44},
                                                                         {22, 44, 48},
                                                                         {23, 46, 52},
                                                                         {24, 48, 56},
                                                                         {25, 50, 64},
                                                                         {26, 52, 72},
                                                                         {27, 54, 80},
                                                                         {28, 56, 88},
                                                                         {29, 58, 96},
                                                                         {30, 60, 104},
                                                                         {31, 62, 112}};

unsigned char InverseQuantiser::intraWeightTable[8][8] = {{8,  16, 19, 22, 26, 27, 29, 34},
                                                          {16, 16, 22, 24, 27, 29, 34, 37},
                                                          {19, 22, 26, 27, 29, 34, 34, 38},
                                                          {22, 22, 26, 27, 29, 34, 37, 40},
                                                          {22, 26, 27, 29, 32, 35, 40, 48},
                                                          {26, 27, 29, 32, 35, 40, 48, 58},
                                                          {26, 27, 29, 34, 38, 46, 56, 69},
                                                          {27, 29, 35, 38, 46, 56, 69, 83}};


void InverseQuantiser::performInverseQuantisation(HPicture *picture) {//TODO
    if (picture->getState() != HPicture::decoding_state::inverse_scanned)
        throw VideoException("InverseQuantiser::performInverseQuantisation: received picture in incorrect state.\n");
    for (size_t s = 0; s < picture->getNumSlices(); s++) {
        Slice *slice = picture->getSlices()[s];
        if (qsc == 0 || (slice->getQuantiserScaleCode() && qsc != slice->getQuantiserScaleCode())) {
            qsc = slice->getQuantiserScaleCode();
        }
        for (size_t m = 0; m < slice->getNumMacroblocks(); m++) {
            Macroblock *macroblock = slice->getMacroblocks()[m];
            if (qsc == 0 || (macroblock->getQuantiserScaleCode() != 0 && qsc != macroblock->getQuantiserScaleCode())) {
                qsc = macroblock->getQuantiserScaleCode();
            }
            for (size_t b = 0; b < macroblock->getBlockCount(); b++) {
                Block *block = macroblock->getBlocks()[b];
                if (block) performInverseQuantisationHelp(block, macroblock);
            }
        }
    }
    picture->setState(HPicture::decoding_state::inverse_quantised);
}

void InverseQuantiser::performInverseQuantisationHelp(Block *block, Macroblock *macroblock) {
    PictureDecoder *pictureDecoder = VideoDecoder::getInstance()->getPictureDecoder();
    bool intra = macroblock->getMacroBlockModes()->isMacroblockIntra();
    PictureCodingExtensionPacket::intra_dc_precision_bits precisionBits = pictureDecoder->getIntraDcPrecision();
    int intra_dc_mult = precisionBits == PictureCodingExtensionPacket::intra_dc_precision_bits::p_8 ? 8 :
                        (precisionBits == PictureCodingExtensionPacket::intra_dc_precision_bits::p_9 ? 4 :
                         (precisionBits == PictureCodingExtensionPacket::intra_dc_precision_bits::p_10 ? 2 : 1));
    int *qFScanned = block->getData();
    int *fPrimePrime = (int *) malloc(sizeof(int) * 8 * 8);
    int *fPrime = (int *) malloc(sizeof(int) * 8 * 8);
    int *quantized = (int *) malloc(sizeof(int) * 8 * 8);
    size_t w = intra ? (block->getCc() == 0 ? 0 : 2) : (block->getCc() == 0 ? 1 : 3);
    for (size_t v = 0; v < 8; v++) {
        for (size_t u = 0; u < 8; u++) {
            if ((u == 0) && (v == 0) && (intra)) {
                fPrimePrime[v * 8 + u] = intra_dc_mult * qFScanned[v * 8 + u];
            } else {
                if (intra) {
                    fPrimePrime[v * 8 + u] = (qFScanned[v * 8 + u] * WEIGHT *
                                              generateQuantiserScale(pictureDecoder->isQScaleType(), qsc) * 2) / 32;
                } else {
                    fPrimePrime[v * 8 + u] = (((qFScanned[v * 8 + u] * 2) + Sign(qFScanned[v * 8 + u])) * WEIGHT
                                              * generateQuantiserScale(pictureDecoder->isQScaleType(), qsc)) / 32;
                }
            }
        }
    }
    int sum = 0;
    for (size_t v = 0; v < 8; v++) {
        for (size_t u = 0; u < 8; u++) {
            if (fPrimePrime[v * 8 + u] > 2047) {
                fPrime[v * 8 + u] = 2047;
            } else {
                if (fPrimePrime[v * 8 + u] < -2048) {
                    fPrime[v * 8 + u] = -2048;
                } else {
                    fPrime[v * 8 + u] = fPrimePrime[v * 8 + u];
                }
            }
            sum = sum + fPrime[v * 8 + u];
            quantized[v * 8 + u] = fPrime[v * 8 + u];
        }
    }
    if ((sum & 1) == 0) {
        if ((quantized[7 * 8 + 7] & 1) != 0) {
            quantized[7 * 8 + 7] = fPrime[7 * 8 + 7] - 1;
        } else {
            quantized[7 * 8 + 7] = fPrime[7 * 8 + 7] + 1;
        }
    }
    block->setData(quantized);
    free(fPrimePrime);
    free(fPrime);
}

unsigned char InverseQuantiser::generateQuantiserScale(bool q_scale_type, unsigned char quantiser_scale_code) {
    if (quantiser_scale_code == 0) {
        throw VideoException("InverseQuantiser::generateQuantiserScale: got forbidden quantiser_scale_code value");
    }
    for (quantiserTable qt : conversion_table) {
        if (qt.quantiser_scale_code == quantiser_scale_code) {
            return q_scale_type ? qt.scale_type_1 : qt.scale_type_0;
        }
    }
    throw VideoException("InverseQuantiser::generateQuantiserScale: reached end of conversion_table");
}

unsigned char InverseQuantiser::generateWeightingValue(size_t u, size_t v, size_t w, bool intra) {
    if (intra) {
        return intraWeightTable[w][InverseScanner::scan_0[v][u]];
    }
    return 16;
}