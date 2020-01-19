//
// Created by elnsa on 2020-01-19.
//

#ifndef PROJECT_CODE_CODEDBLOCKPATTERN_H
#define PROJECT_CODE_CODEDBLOCKPATTERN_H


class CodedBlockPattern {
private: //TODO add VLC fields
    unsigned short coded_block_pattern_420;
    unsigned char coded_block_pattern_1;
    unsigned char coded_block_pattern_2;
public:
    struct initializerStruct {
        bool bla;
        //TODO
    };

    CodedBlockPattern(initializerStruct init);

    ~CodedBlockPattern() = default;

    void print();

    bool operator==(const CodedBlockPattern &rhs) const;

    bool operator!=(const CodedBlockPattern &rhs) const;
};


#endif //PROJECT_CODE_CODEDBLOCKPATTERN_H
