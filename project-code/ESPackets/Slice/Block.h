//
// Created by elnsa on 2020-01-18.
//

#ifndef PROJECT_CODE_BLOCK_H
#define PROJECT_CODE_BLOCK_H


class Block {
    unsigned short dct_dc_size_lum_chrom;
    unsigned short num_dct_coefficients;
    unsigned int* dct_coefficients; //TODO see clause 7
};


#endif //PROJECT_CODE_BLOCK_H
