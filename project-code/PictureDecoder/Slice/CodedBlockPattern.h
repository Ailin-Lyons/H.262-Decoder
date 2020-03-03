//
// Created by elnsa on 2020-01-19.
//

#ifndef PROJECT_CODE_CODEDBLOCKPATTERN_H
#define PROJECT_CODE_CODEDBLOCKPATTERN_H

/**
 * This class represents coded_block_pattern () from H262 6.2.5.3
 */
class CodedBlockPattern {
private:
    unsigned char cbp;
    unsigned char coded_block_pattern_1;
    unsigned char coded_block_pattern_2;

public:
    struct initializerStruct {
        unsigned char cbp;
        unsigned char coded_block_pattern_1;
        unsigned char coded_block_pattern_2;
    };

    explicit CodedBlockPattern(initializerStruct init);

    ~CodedBlockPattern() = default;

    void print();

    bool operator==(const CodedBlockPattern &rhs) const;

    bool operator!=(const CodedBlockPattern &rhs) const;

    unsigned char getCbp() const;

    unsigned char getCodedBlockPattern1() const;

    unsigned char getCodedBlockPattern2() const;

};


#endif //PROJECT_CODE_CODEDBLOCKPATTERN_H
