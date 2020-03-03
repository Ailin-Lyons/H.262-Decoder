//
// Created by elnsa on 2020-01-15.
//
#include "../ESParser.h"
#include "../../StreamPackets/ESPackets/RegularStartCodes/PictureHeaderPacket.h"

class PictureHeaderParser {
public:
    /**
     * Builds a PictureHeaderPacket from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.3
     */
    static PictureHeaderPacket *getNextPacket() {
        ESParser *esParser = ESParser::getInstance();
        PictureHeaderPacket::initializerStruct init = {};
        init.temporal_reference = (unsigned short) esParser->popNBits(10);
        init.picture_coding_type = PictureHeaderPacket::toPictureCodingType((unsigned char) esParser->popNBits(3));
        init.vbv_delay = (unsigned short) esParser->popNBits(16);
        if (init.picture_coding_type == PictureHeaderPacket::picture_coding_types::predictive_coded
            ||
            init.picture_coding_type == PictureHeaderPacket::picture_coding_types::bidirectionally_predictive_coded) {
            esParser->popNBits(4); //Skipping full_pel_backward_vector and backward_f_code as they are not needed
        }
        if (init.picture_coding_type == PictureHeaderPacket::picture_coding_types::bidirectionally_predictive_coded) {
            esParser->popNBits(4); //Skipping full_pel_backward_vector and backward_f_code  as they are not needed
        }
        while (esParser->popNBits(1) == 1) {
            esParser->popNBits(9);  //Skipping extra_bit_picture and extra_information_picture  as they are not needed
        }
        esParser->popNBits(1); //Skipping extra_bit_picture as it is not needed
        return new PictureHeaderPacket(init);
    }
};
