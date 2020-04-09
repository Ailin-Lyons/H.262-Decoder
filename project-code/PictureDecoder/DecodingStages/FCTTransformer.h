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
    static void performSaturation(int* arr, const double* final);
    static int genCoff(int i, int j, const int* quantized);

public:
    static void performIDCTThreaded(HPicture *picture);
    static void performIDCTBlockHelper(Block *block);
    static void performIdctRow(double* arr, const int* quantized);
    static void performIdctCol(double* arr, const double* quantized);
    static void chenIdct(int rowCol, double* arr, const double* quantized);
};


#endif //PROJECT_CODE_DISCRETECOSINETRANSFORMER_H
