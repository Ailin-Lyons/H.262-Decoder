//
// Created by elnsa on 2020-01-15.
//
#include "../ESParser.h"
#include "../../ESPackets/RegularStartCodes/SlicePacket.h"

class SliceParser {
public:
    /**
     * // TODO write comment
     */
    static SlicePacket *getNextPacket(unsigned char i) {
        ESParser *esParser = ESParser::getInstance();
        return new SlicePacket(SlicePacket::initializerStruct{i}); //TODO
    }
};
