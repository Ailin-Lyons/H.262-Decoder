//
// Created by elnsa on 2020-01-16.
//

#include "../ESParser.h"
#include "../../ESPackets/RegularStartCodes/PictureCodingExtensionPacket.h"

class PictureCodingExtensionParser {
public:
    /**
     * Builds a PictureCodingExtensionPacket from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.3.1
     */
    static PictureCodingExtensionPacket *getNextPacket() {
        ESParser *esParser = ESParser::getInstance();
        //PictureCodingExtensionPacket::initializerStruct init = {};
        //TODO
        //return new PictureCodingExtensionPacket(init);
        return nullptr;
    }
};
