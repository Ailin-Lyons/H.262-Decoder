//
// Created by elnsa on 2020-01-15.
//
#include "../ESParser.h"
#include "../../StreamPackets/ESPackets/RegularStartCodes/SequenceExtensionPacket.h"


class SequenceExtensionParser {
public:
    /**
    * Builds a SequenceExtensionParser from ESParser data, starting after the start_code/stream_id
    * H.262 6.2.2.3
    */
    static SequenceExtensionPacket *getNextPacket(unsigned char extension_start_code_identifier) {
        ESParser *esParser = ESParser::getInstance();
        SequenceExtensionPacket::initializerStruct init = {};
        init.e_type = ExtensionPacket::getExtensionCode(extension_start_code_identifier);
        init.profile_and_level_indication = esParser->popNBits(8);
        init.progressive_sequence = esParser->popNBits(1);
        init.chroma_format = SequenceExtensionPacket::getChromaFormatCode(esParser->popNBits(2));
        init.horizontal_size_extension = esParser->popNBits(2);
        init.vertical_size_extension = esParser->popNBits(2);
        init.bit_rate_extension = esParser->popNBits(12);
        esParser->popNBits(1);
        init.vbv_buffer_size_extension = esParser->popNBits(8);
        init.low_delay = esParser->popNBits(1);
        init.frame_rate_extension_n = esParser->popNBits(2);
        init.frame_rate_extension_d = esParser->popNBits(5);
        return new SequenceExtensionPacket(init);
    }
};
