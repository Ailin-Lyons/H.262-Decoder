//
// Created by elnsa on 2020-01-29.
//

#include "FCTTransformer.h"
#include "../VideoDecoder/VideoException.cpp"
#include <cmath>
#include <pthread.h>
#include <ctime>


bool FCTTransformer::initFlag = false;

void FCTTransformer::performIDCTThreaded(HPicture *picture) {
    if (!initFlag) {
        ForeignIDCT::init_idct();
        initFlag = true;
    }
    clock_t t = clock();
    if (picture->getState() != HPicture::decoding_state::inverse_quantised)
        throw VideoException("FCTTransformer: received picture in incorrect state.\n");
    if (picture->getNumSlices() > 0) {
        pthread_t* threads = (pthread_t *) malloc(sizeof(pthread_t) * picture->getNumSlices());
        for (size_t s = 0; s < picture->getNumSlices(); s++) {
            Slice *slice = picture->getSlices()[s];
            pthread_create(&threads[s], nullptr, performIDCTThreadHelper, slice);
        }
        for (size_t i = 0; i < picture->getNumSlices(); i++) {
            pthread_join(threads[i], nullptr);
        }
        free(threads);
    }
    printf("IDCT on picture took %f seconds\n", ((float) clock() - t) / CLOCKS_PER_SEC);
    picture->setState(HPicture::decoding_state::discrete_cosine_transformed);
}

void *FCTTransformer::performIDCTThreadHelper(void *slice) {
    Slice* sl = (Slice *) slice;
    for (size_t m = 0; m < sl->getNumMacroblocks(); m++) {
        Macroblock *macroblock = &sl->getMacroblocks()[m];
        for (size_t b = 0; b < macroblock->getBlockCount(); b++) {
            Block *block = macroblock->getBlocks()[b];
            if (block) performIDCTBlockHelper(block);
        }
    }
    pthread_exit(nullptr);
    return nullptr;
}

void FCTTransformer::performIDCTBlockHelper(Block *block) {//TODO
    auto idctFinal = (int *) malloc(sizeof(int) * 8 * 8);
    memcpy(idctFinal, block->getFquantized(), sizeof(int)*64);
    ForeignIDCT::idct(idctFinal);
    block->setFdctransformed(idctFinal);
}

