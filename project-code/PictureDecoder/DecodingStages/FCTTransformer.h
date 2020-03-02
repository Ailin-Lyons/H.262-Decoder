//
// Created by bhave on 2/19/2020.
//

#ifndef PROJECT_CODE_FCTTRANSFORMER_H
#define PROJECT_CODE_FCTTRANSFORMER_H

#include "ForeignIDCT.cpp"
#include "../Slice/Block.h"
#include "../HPicture.h"

class FCTTransformer {
private:
//    static bool initFlag;
    static double cosab[64];
    static void *performIDCTThreadHelper(void *slice);
    static void performIdctRow(int* arr, const int* quantized);
    static void performIdctCol(int* arr, const int* quantized);

public:
    static void performIDCTThreaded(HPicture *picture);
    static void performIDCTBlockHelper(Block *block);
};


#endif //PROJECT_CODE_DISCRETECOSINETRANSFORMER_H
