//
// Created by elnsa on 2020-01-29.
//

#ifndef PROJECT_CODE_INVERSEQUANTISER_H
#define PROJECT_CODE_INVERSEQUANTISER_H


#include <HPicture.h>

class InverseQuantiser {

public:
    static void performInverseQuantisation(HPicture *picture);

private:
    static void performInverseQuantisationHelp(Block* block, PictureDecoder* pictureDecoder,
            Macroblock* macroblock);
    static unsigned char generateQuantiserScale(bool q_scale_type, unsigned char quantiser_scale_code);
    static unsigned char generateWeightingValue(size_t u, size_t v, size_t w, bool intra);

    struct quantiserTable {
        unsigned char quantiser_scale_code;
        unsigned char scale_type_0;
        unsigned char scale_type_1;
    };

    static quantiserTable conversion_table[32];
    static unsigned char intraWeightTable[8][8];
    static unsigned char qsc;
};


#endif //PROJECT_CODE_INVERSEQUANTISER_H
