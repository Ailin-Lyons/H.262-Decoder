//
// Created by elnsa on 2020-02-10.
//

#ifndef PROJECT_CODE_ALTERNATEIDCT_H
#define PROJECT_CODE_ALTERNATEIDCT_H


#include <HPicture.h>

class AlternateIDCT {
private:
    static long double squirt;
    static long double cosab[64];

public:
    static void performIDCTNaive(HPicture *picture);

    static void performIDCTonBlock(Block *block);

    static void performRealIDCT(long double *realArray, int *sourceArray);

    static void performRound(int *destArray, const long double *sourceArray);

    static void performSaturation(int *array);

    static long double realIDCTHelper(size_t y, size_t x, const int *sourceArray);
};


#endif //PROJECT_CODE_ALTERNATEIDCT_H
