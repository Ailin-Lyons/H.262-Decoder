//
// Created by elnsa on 2020-01-29.
//

#include "InverseDCTransformer.h"
#include "../VideoDecoder/VideoException.cpp"
#include <cmath>
#include <pthread.h>
#include <ctime>

#define C(x) ((x) == 0 ? (1/sqrt(2)) : 1)
#define arg(x) (((2*(x)+1)*u*pi)/16)
#define saturate(x) ((x) < -256 ? -256 : ((x) > 255 ? 255 : (x)))

void InverseDCTransformer::performIDCTNaive(HPicture *picture) {//TODO
    clock_t t = clock();
    if (picture->getState() != HPicture::decoding_state::inverse_quantised)
        throw VideoException("InverseScanner: received picture in incorrect state.\n");
    for (size_t s = 0; s < picture->getNumSlices(); s++) {
        Slice *slice = picture->getSlices()[s];
        for (size_t m = 0; m < slice->getNumMacroblocks(); m++) {
            Macroblock *macroblock = &slice->getMacroblocks()[m];
            for (size_t b = 0; b < macroblock->getBlockCount(); b++) {
                Block *block = macroblock->getBlocks()[b];
                if (block) performIDCTBlockHelper(block);
            }
        }
    }
    printf("IDCTNaive on picture took %f seconds\n", ((float) clock() - t) / CLOCKS_PER_SEC);
    picture->setState(HPicture::decoding_state::discrete_cosine_transformed);
}

void InverseDCTransformer::performIDCTThreaded(HPicture *picture) {
    clock_t t = clock();
    if (picture->getState() != HPicture::decoding_state::inverse_quantised)
        throw VideoException("InverseDCTransformer: received picture in incorrect state.\n");
    if (picture->getNumSlices() > 0) {
        pthread_t *threads = (pthread_t *) malloc(sizeof(pthread_t) * picture->getNumSlices());
        for (size_t s = 0; s < picture->getNumSlices(); s++) {
            Slice *slice = picture->getSlices()[s];
            pthread_create(&threads[s], NULL, performIDCTThreadHelper, slice);
        }
        for (size_t i; i < picture->getNumSlices(); i++) {
            pthread_join(threads[i], NULL);
        }
        free(threads);
    }
    printf("IDCT on picture took %f seconds\n", ((float) clock() - t) / CLOCKS_PER_SEC);
    picture->setState(HPicture::decoding_state::discrete_cosine_transformed);
}

void *InverseDCTransformer::performIDCTThreadHelper(void *slice) {
    Slice *sl = (Slice *) slice;
    for (size_t m = 0; m < sl->getNumMacroblocks(); m++) {
        Macroblock *macroblock = &sl->getMacroblocks()[m];
        for (size_t b = 0; b < macroblock->getBlockCount(); b++) {
            Block *block = macroblock->getBlocks()[b];
            if (block) performIDCTBlockHelper(block);
        }
    }
    pthread_exit(NULL);
    return NULL;
}

void InverseDCTransformer::performIDCTBlockHelper(Block *block) {//TODO
    int *quantized = block->getFquantized();
    auto idctFinal = (int *) malloc(sizeof(double) * 8 * 8);
    for (size_t x = 0; x < 8; x++) {
        for (size_t y = 0; y < 8; y++) {
            idctFinal[x * 8 + y] = genCoff(x, y, quantized);
        }
    }
    block->setFdctransformed(idctFinal);
}

int InverseDCTransformer::genCoff(size_t x, size_t y, const int *quantized) {
    double out = 0;
    for (size_t u = 0; u < 8; u++) {
        for (size_t v = 0; v < 8; v++) {
            out += C(u) * C(v) * quantized[v * 8 + u] * cos(arg(x)) * cos(arg(y));
        }
    }
    return saturate(round(0.25 * out));
}