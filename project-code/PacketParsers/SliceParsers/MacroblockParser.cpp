//
// Created by elnsa on 2020-01-19.
//
#include "ESParser.h"
#include "../../ESPackets/Slice/Macroblock.h"

#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

class MacroblockParser {
public:
    /**
     * Builds a Macroblock() from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.5.1
     */
    static Macroblock *getNextPacket(unsigned char stream_id) {
        return nullptr; //TODO
    }
};
