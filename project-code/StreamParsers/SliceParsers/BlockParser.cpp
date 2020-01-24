//
// Created by elnsa on 2020-01-19.
//
#include "ESParser.h"
#include "../../StreamPackets/ESPackets/Slice/Block.h"

#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

class BlockParser {
public:
    /**
     * Builds a Block() from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.6
     */
    static Block *getNextPacket() {
        return nullptr; //TODO
    }
};

