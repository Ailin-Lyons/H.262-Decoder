//
// Created by bhave on 2/19/2020.
//

#ifndef PROJECT_CODE_FCTTRANSFORMER_H
#define PROJECT_CODE_FCTTRANSFORMER_H

#include <HPicture.h>
#include "ForeignIDCT.cpp"

class FCTTransformer {
private:
    static bool initFlag;
    static void *performIDCTThreadHelper(void *slice);
    static void performIDCTBlockHelper(Block *block);
public:
    static void performIDCTThreaded(HPicture *picture);
};


#endif //PROJECT_CODE_DISCRETECOSINETRANSFORMER_H
