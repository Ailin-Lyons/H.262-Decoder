//
// Created by elnsa on 2020-01-19.
//

#ifndef PROJECT_CODE_MACROBLOCKPARSER_H
#define PROJECT_CODE_MACROBLOCKPARSER_H
//
// Created by elnsa on 2020-01-19.
//
#include "ESParser.h"
#include "../../ESPackets/Slice/Macroblock.h"
#include "MacroblockModesParser.h"

#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

class MacroblockParser {
private:
    struct vlc {
        unsigned char numbits;
        unsigned char value;
        unsigned short key;
    };
    static vlc table_b1[];

public:
/**
     * Builds a Macroblock() from ESParser data, starting after the start_code/stream_id
     * and stores it in mb
     * H.262 6.2.5.1
     */
    static Macroblock *getNextPacket(Macroblock *mb);

private:
    static size_t getAddressIncrement();
};


#endif //PROJECT_CODE_MACROBLOCKPARSER_H
