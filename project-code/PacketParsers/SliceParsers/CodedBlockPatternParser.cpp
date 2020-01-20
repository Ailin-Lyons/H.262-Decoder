//
// Created by elnsa on 2020-01-19.
//
#include "ESParser.h"
#include "../../ESPackets/Slice/CodedBlockPattern.h"

#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

class CodedBlockPatternParser {
public:
    /**
     * Builds a CodedBlockPattern() from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.5.3
     */
    static CodedBlockPattern *getNextPacket() {
        return nullptr; //TODO
    }
};
