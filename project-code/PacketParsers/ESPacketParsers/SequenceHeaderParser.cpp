//
// Created by elnsa on 2020-01-15.
//
#include "../ESParser.h"
#include "../../ESPackets/RegularStartCodes/SequenceHeaderPacket.h"

class SequenceHeaderParser {
public:
    /**
    * Builds a SequenceHeaderPacket from ESParser data, starting after the start_code/stream_id
    * H.262 6.2.3
    */
    static SequenceHeaderPacket *getNextPacket() {
        ESParser *esParser = ESParser::getInstance();
        SequenceHeaderPacket::initializerStruct init = {};
        init.horizontal_size_value = esParser->popNBits(12);
        init.vertical_size_value = esParser->popNBits(12);
        init.aspect_ratio_information = esParser->popNBits(4);
        init.frame_rate_code = esParser->popNBits(4);
        init.bit_rate_value = esParser->popNBits(18);
        esParser->popNBits(1); //Skipping marker bit
        init.vbv_buffer_size_value = esParser->popNBits(10);
        init.constrained_parameters_flag = esParser->popNBits(1);
        init.load_intra_quantiser_matrix = esParser->popNBits(1);
        if (init.load_intra_quantiser_matrix) {
            init.intra_quantiser_matrix = (unsigned char *) malloc(sizeof(unsigned char) * 64);
            for(int i = 0; i < 64; i++){
                init.intra_quantiser_matrix[i] = esParser->popNBits(8);
            }
        }
        init.load_non_intra_quantiser_matrix = esParser->popNBits(1);
        if (init.load_non_intra_quantiser_matrix) {
            init.non_intra_quantiser_matrix = (unsigned char *) malloc(sizeof(unsigned char) * 64);
            for(int i = 0; i < 64; i++){
                init.non_intra_quantiser_matrix[i] = esParser->popNBits(8);
            }
        }
        return new SequenceHeaderPacket(init);
    }
};

