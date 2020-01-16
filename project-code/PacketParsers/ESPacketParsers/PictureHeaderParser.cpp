//
// Created by elnsa on 2020-01-15.
//
#include "../ESParser.h"
#include "../../ESPackets/RegularStartCodes/PictureHeaderPacket.h"

class PictureHeaderParser {
public:
    /**
     * Builds a PictureHeaderPacket from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.3
     */
    static PictureHeaderPacket *getNextPacket() {
        ESParser *esParser = ESParser::getInstance();
        PictureHeaderPacket::initializerStruct init = {};
        init.temporal_reference = esParser->popNBits(10);
        init.picture_coding_type = esParser->popNBits(3);
        init.vbv_delay = esParser->popNBits(16);
        if (init.picture_coding_type == 2 || init.picture_coding_type == 3) {
            esParser->popNBits(4); //Skipping full_pel_backward_vector and backward_f_code as they are not needed
        }
        if (init.picture_coding_type == 3) {
            esParser->popNBits(4); //Skipping full_pel_backward_vector and backward_f_code  as they are not needed
        }
        while(esParser->popNBits(1) == 1){
            esParser->popNBits(9);  //Skipping extra_bit_picture and extra_information_picture  as they are not needed
        }
        esParser->popNBits(1); //Skipping extra_bit_picture as it is not needed
        esParser->next_start_code();
        return new PictureHeaderPacket(init);
    }
};
