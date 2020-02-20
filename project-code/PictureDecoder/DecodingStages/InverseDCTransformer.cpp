//
// Created by elnsa on 2020-01-29.
//

#include "InverseDCTransformer.h"
#include "../VideoDecoder/VideoException.cpp"
#include <cmath>
#include <pthread.h>
#include <ctime>


double InverseDCTransformer::cosab[64] = {1,
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


#define C(x) ((x) == 0 ? (0.707106781186547524400844362104849039284835937688) : 1)
#define SATURATE(x) ((x) < -256 ? -256 : ((x) > 255 ? 255 : (x)))

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

void *InverseDCTransformer::performIDCTThreadHelper(void *slice) {
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

void InverseDCTransformer::performIDCTBlockHelper(Block *block) {//TODO
    int *quantized = block->getFquantized();
    auto idctFinal = (int *) malloc(sizeof(double) * 8 * 8);
    for (size_t y = 0; y < 8; y++) {
        for (size_t x = 0; x < 8; x++) {
            idctFinal[y * 8 + x] = genCoff(x, y, quantized);
        }
    }
    block->setFdctransformed(idctFinal);
}

int InverseDCTransformer::genCoff(size_t x, size_t y, const int *quantized) {
    double out = 0;
    for (size_t v = 0; v < 8; v++) {
        for (size_t u = 0; u < 8; u++) {
            out += C(u) * C(v) * quantized[v * 8 + u] * cosab[u * 8 + x] * cosab[v * 8 + y];
        }
    }
    return SATURATE(round(0.25 * out));
}
