//
// Created by elnsa on 2020-01-23.
//

#ifndef PROJECT_CODE_BLOCKPARSER_H
#define PROJECT_CODE_BLOCKPARSER_H

#include "ESParser.h"
#include "../../StreamPackets/ESPackets/Slice/Block.h"


#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

class BlockParser {
private:
    struct vlc {
        unsigned char numbits;
        unsigned short value;
        unsigned short key;
    };
    static vlc table_b12[];
    static vlc table_b13[];
public:
    /**
     * Builds a Block() from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.6
     */
    static Block *block(size_t i);

private:
    static unsigned char getDctDcSizeLuminance();

    static unsigned char getDctDcSizeChrominance();

    static unsigned char getDctDcSize(unsigned char cc);

    static void initializePatternCode(bool pattern_code[12]);

    static unsigned char getCC(size_t i);
};


#endif //PROJECT_CODE_BLOCKPARSER_H
