//
// Created by elnsa on 2020-02-10.
//

#include <VideoDecoder.h>
#include "AlternateQuantiser.h"
#include "../../VideoDecoder/VideoException.cpp"

int AlternateQuantiser::w0[64] = {8, 16, 19, 22, 26, 27, 29, 34,
                                  16, 16, 22, 24, 27, 29, 34, 37,
                                  19, 22, 26, 27, 29, 34, 34, 38,
                                  22, 22, 26, 27, 29, 34, 37, 40,
                                  22, 26, 27, 29, 32, 35, 40, 48,
                                  26, 27, 29, 32, 35, 40, 48, 58,
                                  26, 27, 29, 34, 38, 46, 56, 69,
                                  27, 29, 35, 38, 46, 56, 69, 83};

AlternateQuantiser::quantiserTable AlternateQuantiser::conversion_table[] = {{1,  2,  1},
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


void AlternateQuantiser::performInverseQuantisation(HPicture *picture) {
    for (size_t s = 0; s < picture->getNumSlices(); s++) {
        Slice *slice = picture->getSlices()[s];
        for (size_t m = 0; m < slice->getNumMacroblocks(); m++) {
            Macroblock *macroblock = slice->getMacroblocks()[m];
            int quantiser_scale_code = macroblock->getQuantiserScaleCode();
            bool intra = macroblock->getMacroBlockModes()->isMacroblockIntra();
            for (size_t b = 0; b < macroblock->getBlockCount(); b++) {
                Block *block = macroblock->getBlocks()[b];
                if (block) performIQonBlock(block, quantiser_scale_code, intra);
            }
        }
    }
    picture->setState(HPicture::decoding_state::inverse_quantised);
}

void AlternateQuantiser::performIQonBlock(Block *block, int quantiser_scale_code, bool intra) {
    int *array = (int *) malloc(sizeof(int) * 8 * 8);
    performIQA(array, block->getQFscanned(), quantiser_scale_code, intra);
    performSaturation(array);
    performMismatchControl(array);
    block->setFquantized(array);
}

void AlternateQuantiser::performSaturation(int *array) {
    for (size_t i = 0; i < 64; i++) {
        if (array[i] > 2047) array[i] = 2047;
        else if (array[i] < -2048) array[i] = -2048;
    }
}

void AlternateQuantiser::performMismatchControl(int *array) {
    int sum = 0;
    for (size_t i = 0; i < 64; i++) {
        sum += array[i];
    }
    if (sum % 2 == 0) {
        if (array[63] % 2 == 1) {
            array[63]--;
        } else {
            array[63]++;
        }
    }
}

void AlternateQuantiser::performIQA(int *outArray, int *inArray, int quantiser_scale_code, bool intra) {
    bool q_scale_type = VideoDecoder::getInstance()->getPictureDecoder()->isQScaleType();
    int quantiser_scale = getQuantiserScale(quantiser_scale_code, q_scale_type);
    for (size_t i = 0; i < 64; i++) {
        if (i == 0 && intra) {
            outArray[i] = performDCQuantisation(inArray[i]);
        } else if (intra) {
            outArray[i] = (inArray[i] * w0[i] * quantiser_scale * 2) / 32;
        } else {
            outArray[i] = (((inArray[i] * 2) + Sign(inArray[i])) * w0[i] * quantiser_scale) / 32;
        }
    }
}

int AlternateQuantiser::performDCQuantisation(int dcCoef) {
    int mult;
    switch (VideoDecoder::getInstance()->getPictureDecoder()->getIntraDcPrecision()) {
        case PictureCodingExtensionPacket::intra_dc_precision_bits::p_8:
            mult = 8;
            break;
        case PictureCodingExtensionPacket::intra_dc_precision_bits::p_9:
            mult = 4;
            break;
        case PictureCodingExtensionPacket::intra_dc_precision_bits::p_10:
            mult = 2;
            break;
        case PictureCodingExtensionPacket::intra_dc_precision_bits::p_11:
            mult = 1;
            break;
    }
    return dcCoef * mult;
}

int AlternateQuantiser::getQuantiserScale(int code, bool type) {
    for (size_t i = 0; i < 32; i++) { // NOLINT(modernize-loop-convert)
        if (conversion_table[i].quantiser_scale_code == code) {
            if (type) return conversion_table[i].scale_type_1;
            else return conversion_table[i].scale_type_0;
        }
    }
    throw VideoException("InverseQuantiser::getQuantiserScale: no valid code found");
}

int AlternateQuantiser::Sign(int in) {
    if (in > 0) return 1;
    if (in < 0) return -1;
    return 0;
}
