//
// Created by elnsa on 2020-02-10.
//

#ifndef PROJECT_CODE_ALTERNATEQUANTISER_H
#define PROJECT_CODE_ALTERNATEQUANTISER_H


#include <HPicture.h>

class AlternateQuantiser {
private:

    struct quantiserTable {
        int quantiser_scale_code;
        int scale_type_0;
        int scale_type_1;
    };

    static int w0[64];
    static quantiserTable conversion_table[32];

public:
    static void performInverseQuantisation(HPicture *picture);

    static void performIQonBlock(Block *block, int i, bool b);

    static void performSaturation(int *array);

    static void performMistmatchControl(int *array);

    static void performIQA(int *outArray, int *inArray, int i, bool b);

    static int performDCQuantisation(int dcCoef);

    static int getQuantiserScale(int code, bool type);

    static int Sign(int in);
};


#endif //PROJECT_CODE_ALTERNATEQUANTISER_H
