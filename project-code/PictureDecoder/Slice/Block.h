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
    int *QFS;
    int *QFscanned;
    int *Fquantized;
    int *fdctransformed;
public:
    int *getQfs() const;

    void setQfs(int *qfs);

    int *getQFscanned() const;

    void setQFscanned(int *qFscanned);

    int *getFquantized() const;

    void setFquantized(int *fquantized);

    int *getFdctransformed() const;

    void setFdctransformed(int *fdctransformed);

    unsigned char getCc() const;

public:
    struct initializerStruct {
        size_t i;
        unsigned char cc;
        unsigned char dct_dc_size;
        short dct_dc_differential;
        int *QFS;
    };

    Block(initializerStruct init);

    ~Block();

    void print();

    bool operator==(const Block &rhs) const;

    bool operator!=(const Block &rhs) const;
};


#endif //PROJECT_CODE_BLOCK_H
