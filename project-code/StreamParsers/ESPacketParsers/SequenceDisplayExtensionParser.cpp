//
// Created by elnsa on 2020-01-16.
//

#include "../ESParser.h"
#include "../../StreamPackets/ESPackets/RegularStartCodes/SequenceDisplayExtensionPacket.h"

class SequenceDisplayExtensionParser {
public:
    /**
     * Builds a SequenceDisplayExtensionPacket from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.2.4
     */
    static SequenceDisplayExtensionPacket *getNextPacket() {
        ESParser *esParser = ESParser::getInstance();
        SequenceDisplayExtensionPacket::initializerStruct init = {};
        init.video_format = (unsigned char) esParser->popNBits(3);
        init.colour_description = (bool) esParser->popNBits(1);
        if (init.colour_description) {
            init.colour_primaries = (unsigned char) esParser->popNBits(8);
            init.transfer_characteristics = (unsigned char) esParser->popNBits(8);
            init.matrix_coefficients = (unsigned char) esParser->popNBits(8);
        }
        init.display_horizontal_size = (unsigned short) esParser->popNBits(14);
        esParser->popNBits(1); //marker bit
        init.display_vertical_size = (unsigned short) esParser->popNBits(14);
        return new SequenceDisplayExtensionPacket(init);
    }
};
