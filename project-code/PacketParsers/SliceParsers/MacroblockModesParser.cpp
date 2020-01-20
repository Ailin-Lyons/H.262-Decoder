//
// Created by elnsa on 2020-01-19.
//
#include "ESParser.h"
#include "../../ESPackets/Slice/MacroblockModes.h"

#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

class MacroblockModesParser {
public:
    /**
     * Builds a MacroblockModes() from ESParser data, starting after the start_code/stream_id
     * and stores it at address mbm
     * H.262 6.2.5.1
     */
    static MacroblockModes *getNextPacket(MacroblockModes* mbm) {
        return nullptr; //TODO
    }
};
