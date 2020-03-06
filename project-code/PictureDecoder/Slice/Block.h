//
// Created by elnsa on 2020-01-18.
//

#ifndef PROJECT_CODE_BLOCK_H
#define PROJECT_CODE_BLOCK_H

#include <cstddef>
/**
 * This class represents block(i) from H262 6.2.6 and 7.2
 */
class Block {
private:
    size_t i;
    unsigned char cc;
    unsigned char dct_dc_size;
    short dct_dc_differential;
    int *data;

public:
    int *getData() const;

    void setData(int *block_data);

    unsigned char getCc() const;

public:
    struct initializerStruct {
        size_t i;
        unsigned char cc;
        unsigned char dct_dc_size;
        short dct_dc_differential;
        int *QFS;
    };

    explicit Block(initializerStruct init);

    ~Block();

    void print();

    bool operator==(const Block &rhs) const;

    bool operator!=(const Block &rhs) const;
};


#endif //PROJECT_CODE_BLOCK_H
