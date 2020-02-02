//
// Created by elnsa on 2020-01-29.
//

#ifndef PROJECT_CODE_DISCRETECOSINETRANSFORMER_H
#define PROJECT_CODE_DISCRETECOSINETRANSFORMER_H


#include <HPicture.h>

class InverseDCTransformer {

public:
    constexpr const static double pi = 3.14159265359;
    static void performInverseDCT(HPicture *picture);
    static void performInverseDCTHelp(Block *block);
    static int genCoff(size_t x, size_t y, const int* quantized);
};


#endif //PROJECT_CODE_DISCRETECOSINETRANSFORMER_H
