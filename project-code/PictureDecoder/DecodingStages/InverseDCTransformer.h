//
// Created by elnsa on 2020-01-29.
//

#ifndef PROJECT_CODE_DISCRETECOSINETRANSFORMER_H
#define PROJECT_CODE_DISCRETECOSINETRANSFORMER_H


#include <HPicture.h>

class InverseDCTransformer {
private:
    static double cosab[64];
    static void *performIDCTThreadHelper(void *slice);
    static void performIDCTBlockHelper(Block *block);
    static int genCoff(size_t x, size_t y, const int* quantized);
public:
    static void performIDCTNaive(HPicture *picture);
    static void performIDCTThreaded(HPicture *picture);
};


#endif //PROJECT_CODE_DISCRETECOSINETRANSFORMER_H
