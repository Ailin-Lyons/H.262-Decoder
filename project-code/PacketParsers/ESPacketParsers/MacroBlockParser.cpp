//
// Created by bhave on 1/18/2020.
//

#include "../../ESPackets/Slice/MacroBlock.h"

#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

class MacroBlockParser {
public:
    /**
     * Builds a MacroBlock from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.4
     */
    static MacroBlock *getNextPacket() {
        return nullptr;
    }
};