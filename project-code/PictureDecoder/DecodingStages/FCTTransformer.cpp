//
// Created by elnsa on 2020-01-29.
//

#include "FCTTransformer.h"
#include "../VideoDecoder/VideoException.cpp"
#include <cmath>
#include <pthread.h>
#include <ctime>



double FCTTransformer::cosab[64] = {1,
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
#define ARG(x,y) (((2*(x)+1)*(y)*M_PI)/16)
//
//bool FCTTransformer::initFlag = false;

void FCTTransformer::performIDCTThreaded(HPicture *picture) {
//    if (!initFlag) {
//        ForeignIDCT::init_idct();
//        initFlag = true;
//    }
    //clock_t t = clock();
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
    //printf("IDCT on picture took %f seconds\n", ((float) clock() - t) / CLOCKS_PER_SEC);
    picture->setState(HPicture::decoding_state::discrete_cosine_transformed);
}

void *FCTTransformer::performIDCTThreadHelper(void *slice) {
    auto sl = (Slice *) slice;
    for (size_t m = 0; m < sl->getNumMacroblocks(); m++) {
        Macroblock *macroblock = sl->getMacroblocks()[m];
        for (size_t b = 0; b < macroblock->getBlockCount(); b++) {
            Block *block = macroblock->getBlocks()[b];
            if (block) performIDCTBlockHelper(block);
        }
    }
    pthread_exit(nullptr);
    return nullptr;
}

void FCTTransformer::performIDCTBlockHelper(Block *block) {//TODO
    int *quantized = block->getData();
    auto idctFinal = (int *) malloc(sizeof(int) * 8 * 8);
    auto tempRowMem = (double*) malloc(sizeof(double) * 8 * 8);
    auto finalMem = (double*) malloc(sizeof(double) * 8 * 8);
    for (size_t i = 0; i < 8; i++) {
        performIdctRow(tempRowMem + 8*i, quantized + 8*i);
    }
    for (size_t j = 0; j < 8; j++) {
        performIdctCol(finalMem + j, tempRowMem + j);
    }
    performSaturation(idctFinal, finalMem);
    block->setData(idctFinal);
}

void FCTTransformer::performSaturation(int* arr, const double* final) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            arr[i*8+j] = (int) SATURATE(round(0.25 * final[i*8+j]));
        }
    }
}

int FCTTransformer::genCoff(int i, int j, const int* quantized) {
    double temp = 0;
    for (int v = 0; v < 8; v++) {
        temp += C(v) * quantized[i * 8 + v] * cos(ARG(j, v));
    }
    for (int u = 0; u < 8; u++) {
        temp += C(u) * quantized[u * 8 + j] * cos(ARG(i, u));
    }
    return SATURATE(round(temp * 0.25));
}

void FCTTransformer::performIdctRow(double* arr, const int* quantized) {
//    // non-wiki implementation
//    for (int n = 0; n < 8; n++) {
//        double temp = 0;
//        for (int k = 0; k < 8; k++) {
//            temp += C(k) * quantized[k] * cos(ARG(n, k));
//        }
//        arr[n] = temp;
//    }

    // wiki implementation
    for (int k = 0; k < 8; k++) {
        double temp = 0;
        for (int n = 1; n < 8; n++) {
            temp += quantized[n] * cos((M_PI / 8) * n * (k + 0.5));
        }
        arr[k] = temp + (C(0) * quantized[0]);
    }
}

void FCTTransformer::performIdctCol(double* arr, const double* quantized) {
//    // non-wiki implementation
//    for (int n = 0; n < 8; n++) {
//        double temp = 0;
//        for (int k = 0; k < 8; k++) {
//            temp += C(k) * quantized[k * 8] * cos(ARG(n, k));
//        }
//        arr[n * 8] = temp * 0.25;
//    }

    // wiki implementation
    for (int k = 0; k < 8; k++) {
        double temp = 0;
        for (int n = 1; n < 8; n++) {
            temp += quantized[n*8] * cos((M_PI / 8) * n * (k + 0.5));
        }
        arr[k*8] = temp + (C(0) * quantized[0]);
    }
}

