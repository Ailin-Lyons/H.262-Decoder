//
// Created by elnsa on 2020-02-10.
//

#include <cmath>
#include "AlternateIDCT.h"

long double AlternateIDCT::squirt = 0.707106781186547524400844362104849039284835937688;
long double AlternateIDCT::cosab[64] = {1,
                                        1,
                                        1,
                                        1,
                                        1,
                                        1,
                                        1,
                                        1,

                                        0.980785280403230449126182236134239036973933730893,
                                        0.831469612302545237078788377617905756738560811987,
                                        0.555570233019602224742830813948532874374937190754,
                                        0.195090322016128267848284868477022240927691617751,
                                        -0.195090322016128267848284868477022240927691617751,
                                        -0.555570233019602224742830813948532874374937190754,
                                        -0.831469612302545237078788377617905756738560811987,
                                        -0.980785280403230449126182236134239036973933730893,

                                        0.923879532511286756128183189396788286822416625863,
                                        0.382683432365089771728459984030398866761344562485,
                                        -0.382683432365089771728459984030398866761344562485,
                                        -0.923879532511286756128183189396788286822416625863,
                                        -0.923879532511286756128183189396788286822416625863,
                                        -0.382683432365089771728459984030398866761344562485,
                                        0.382683432365089771728459984030398866761344562485,
                                        0.923879532511286756128183189396788286822416625863,

                                        0.831469612302545237078788377617905756738560811987,
                                        -0.195090322016128267848284868477022240927691617751,
                                        -0.980785280403230449126182236134239036973933730893,
                                        -0.555570233019602224742830813948532874374937190754,
                                        0.555570233019602224742830813948532874374937190754,
                                        0.980785280403230449126182236134239036973933730893,
                                        0.195090322016128267848284868477022240927691617751,
                                        -0.831469612302545237078788377617905756738560811987,

                                        0.707106781186547524400844362104849039284835937688,
                                        -0.707106781186547524400844362104849039284835937688,
                                        -0.707106781186547524400844362104849039284835937688,
                                        0.707106781186547524400844362104849039284835937688,
                                        0.707106781186547524400844362104849039284835937688,
                                        -0.707106781186547524400844362104849039284835937688,
                                        -0.707106781186547524400844362104849039284835937688,
                                        0.707106781186547524400844362104849039284835937688,

                                        0.555570233019602224742830813948532874374937190754,
                                        -0.980785280403230449126182236134239036973933730893,
                                        0.195090322016128267848284868477022240927691617751,
                                        0.831469612302545237078788377617905756738560811987,
                                        -0.831469612302545237078788377617905756738560811987,
                                        -0.831469612302545237078788377617905756738560811987,
                                        0.980785280403230449126182236134239036973933730893,
                                        -0.555570233019602224742830813948532874374937190754,

                                        0.382683432365089771728459984030398866761344562485,
                                        -0.923879532511286756128183189396788286822416625863,
                                        0.923879532511286756128183189396788286822416625863,
                                        -0.382683432365089771728459984030398866761344562485,
                                        -0.382683432365089771728459984030398866761344562485,
                                        0.923879532511286756128183189396788286822416625863,
                                        -0.923879532511286756128183189396788286822416625863,
                                        0.382683432365089771728459984030398866761344562485,

                                        0.195090322016128267848284868477022240927691617751,
                                        -0.555570233019602224742830813948532874374937190754,
                                        0.831469612302545237078788377617905756738560811987,
                                        -0.980785280403230449126182236134239036973933730893,
                                        0.980785280403230449126182236134239036973933730893,
                                        -0.831469612302545237078788377617905756738560811987,
                                        0.555570233019602224742830813948532874374937190754,
                                        -0.195090322016128267848284868477022240927691617751
};

void AlternateIDCT::performIDCTNaive(HPicture *picture) {
    for (size_t s = 0; s < picture->getNumSlices(); s++) {
        Slice *slice = picture->getSlices()[s];
        for (size_t m = 0; m < slice->getNumMacroblocks(); m++) {
            Macroblock *macroblock = &slice->getMacroblocks()[m];
            for (size_t b = 0; b < macroblock->getBlockCount(); b++) {
                Block *block = macroblock->getBlocks()[b];
                if (block) performIDCTonBlock(block);
            }
        }
    }
    picture->setState(HPicture::decoding_state::discrete_cosine_transformed);
}

void AlternateIDCT::performIDCTonBlock(Block *block) {
    block->setFdctransformed((int *) malloc(sizeof(int) * 8 * 8));
    long double realArray[64];
    performRealIDCT((long double *) &realArray, block->getFquantized());
    performRound(block->getFdctransformed(), (long double *) &realArray);
    performSaturation(block->getFdctransformed());
}

void AlternateIDCT::performRealIDCT(long double *realArray, int *sourceArray) {
    for (size_t y = 0; y < 8; y++) {
        for (size_t x = 0; x < 8; x++) {
            realArray[y * 8 + x] = realIDCTHelper(y, x, sourceArray);
        }
    }
}

void AlternateIDCT::performRound(int *destArray, long double *sourceArray) {
    for (size_t i = 0; i < 64; i++) {
        destArray[i] = (int) (sourceArray[i] + 0.5 - (sourceArray[i] < 0));
    }
}

void AlternateIDCT::performSaturation(int *array) {
    for (size_t i = 0; i < 64; i++) {
        if (array[i] < -256) array[i] = -256;
        if (array[i] > 255) array[i] = 255;
    }
}

long double AlternateIDCT::realIDCTHelper(size_t y, size_t x, int *sourceArray) {
    long double div = (long double) 4;
    long double out = 0;
    for (size_t u = 0; u < 8; u++) {
        for (size_t v = 0; v < 8; v++) {
            long double cu = 1;
            long double cv = 1;
            if (u == 0) cu = squirt;
            if (v == 0) cv = squirt;
            long double arr = (long double) sourceArray[v * 8 + u];
            out += (cu * cv * arr * cosab[u * 8 + x] * cosab[v * 8 + y]);
        }
    }
    return out / div;
}