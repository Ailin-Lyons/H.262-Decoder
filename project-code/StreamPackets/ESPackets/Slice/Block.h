//
// Created by elnsa on 2020-01-18.
//

#ifndef PROJECT_CODE_BLOCK_H
#define PROJECT_CODE_BLOCK_H


class Block {
private:  //TODO add VLC fields
    unsigned char cc;
    unsigned char dct_dc_size;
    short dct_dc_differential;
    int *QFS; //TODO see clause 7
public:
    struct initializerStruct {
        unsigned char cc;
        unsigned char dct_dc_size;
        short dct_dc_differential;
        int *QFS; //TODO see clause 7
    };

    Block(initializerStruct init);

    ~Block() = default;//TODO

    void print();

    bool operator==(const Block &rhs) const;

    bool operator!=(const Block &rhs) const;
};


#endif //PROJECT_CODE_BLOCK_H
