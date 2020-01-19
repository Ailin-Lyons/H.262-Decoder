//
// Created by elnsa on 2020-01-18.
//

#ifndef PROJECT_CODE_BLOCK_H
#define PROJECT_CODE_BLOCK_H


class Block {
private:  //TODO add VLC fields
    unsigned short dct_dc_size_lum_chrom;
    unsigned short num_dct_coefficients;
    unsigned int *dct_coefficients; //TODO see clause 7
public:
    struct initializerStruct {
        bool bla;
        //TODO
    };

    Block(initializerStruct init);

    ~Block() = default;//TODO

    void print();

    bool operator==(const Block &rhs) const;

    bool operator!=(const Block &rhs) const;
};


#endif //PROJECT_CODE_BLOCK_H
