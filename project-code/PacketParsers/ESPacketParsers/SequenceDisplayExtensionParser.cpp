//
// Created by elnsa on 2020-01-16.
//

#include "../ESParser.h"
#include "../../ESPackets/RegularStartCodes/SequenceDisplayExtensionPacket.h"

class SequenceDisplayExtensionParser {
public:
    /**
     * Builds a SequenceDisplayExtensionPacket from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.2.4
     */
    static SequenceDisplayExtensionPacket *getNextPacket() {
        ESParser *esParser = ESParser::getInstance();
        //SequenceDisplayExtensionPacket::initializerStruct init = {};
        //TODO
        //return new SequenceDisplayExtensionPacket(init);
        return nullptr;
    }
};
