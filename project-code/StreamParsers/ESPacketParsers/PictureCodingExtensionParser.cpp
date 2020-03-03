//
// Created by elnsa on 2020-01-16.
//

#include "../ESParser.h"
#include "../../StreamPackets/ESPackets/RegularStartCodes/PictureCodingExtensionPacket.h"

class PictureCodingExtensionParser {
public:
    /**
     * Builds a PictureCodingExtensionPacket from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.3.1
     */
    static PictureCodingExtensionPacket *getNextPacket() {
        ESParser *esParser = ESParser::getInstance();
        PictureCodingExtensionPacket::initializerStruct init = {};
        init.f_code_0_0 = (unsigned char) esParser->popNBits(4);
        init.f_code_0_1 = (unsigned char) esParser->popNBits(4);
        init.f_code_1_0 = (unsigned char) esParser->popNBits(4);
        init.f_code_1_1 = (unsigned char) esParser->popNBits(4);
        init.intra_dc_precision = PictureCodingExtensionPacket::getIntraDCPrecisionType(
                (unsigned char) esParser->popNBits(2));
        init.picture_structure = PictureCodingExtensionPacket::getPictureStructureType(
                (unsigned char) esParser->popNBits(2));
        init.top_field_first = (bool) esParser->popNBits(1);
        init.frame_pred_frame_dct = (bool) esParser->popNBits(1);
        init.concealment_motion_vectors = (bool) esParser->popNBits(1);
        init.q_scale_type = (bool) esParser->popNBits(1);
        init.intra_vlc_format = (bool) esParser->popNBits(1);
        init.alternate_scan = (bool) esParser->popNBits(1);
        init.repeat_first_field = (bool) esParser->popNBits(1);
        init.chroma_420_type = (bool) esParser->popNBits(1);
        init.progressive_frame = (bool) esParser->popNBits(1);
        init.composite_display_flag = (bool) esParser->popNBits(1);
        if (init.composite_display_flag) {
            init.v_axis = (bool) esParser->popNBits(1);
            init.field_sequence = (unsigned char) esParser->popNBits(3);
            init.sub_carrier = (bool) esParser->popNBits(1);
            init.burst_amplitude = (unsigned char) esParser->popNBits(7);
            init.sub_carrier_phase = (unsigned char) esParser->popNBits(8);
        }
        return new PictureCodingExtensionPacket(init);
    }
};
