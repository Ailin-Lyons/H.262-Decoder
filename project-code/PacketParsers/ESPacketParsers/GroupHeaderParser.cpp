//
// Created by elnsa on 2020-01-15.
//
#include "../ESParser.h"
#include "../../ESPackets/RegularStartCodes/GroupOfPicturesHeaderPacket.h"

class GroupHeaderParser {
public:
    /**
     * Builds a GroupOfPicturesHeaderPacket from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.2.6
     */
    static GroupOfPicturesHeaderPacket *getNextPacket() {
        ESParser *esParser = ESParser::getInstance();
        GroupOfPicturesHeaderPacket::initializerStruct init = {};
        init.time_code  = esParser->popNBits(25);
        init.closed_gop = esParser->popNBits(1);
        init.broken_link = esParser->popNBits(1);
        esParser->next_start_code();
        return new GroupOfPicturesHeaderPacket(init);
    }
};
