//
// Created by elnsa on 2020-01-21.
//

#ifndef PROJECT_CODE_CODEDBLOCKPATTERNPARSER_H
#define PROJECT_CODE_CODEDBLOCKPATTERNPARSER_H

#include "../../StreamPackets/ESPackets/Slice/CodedBlockPattern.h"

class CodedBlockPatternParser {
private:
    struct vlc {
        unsigned char numbits;
        unsigned char value;
        unsigned short key;
    };
    static vlc table_b9[];
public:
    /**
     * Builds a CodedBlockPattern() from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.5.3
     */
    static CodedBlockPattern *coded_block_pattern();

private:

    static unsigned char getCodedBlockPattern();
};

#endif //PROJECT_CODE_CODEDBLOCKPATTERNPARSER_H
