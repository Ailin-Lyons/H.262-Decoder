//
// Created by elnsa on 2020-01-29.
//

#ifndef PROJECT_CODE_INVERSESCANNER_H
#define PROJECT_CODE_INVERSESCANNER_H


#include "../HPicture.h"

class InverseScanner {
private:
    static char scan_0[8][8];

public:
    static void performInverseScan(HPicture *picture, bool alternate_scan);

    static void performInverseScanHelper(Block *block);
};


#endif //PROJECT_CODE_INVERSESCANNER_H