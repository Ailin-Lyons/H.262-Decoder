#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-bool-literals"
//
// Created by elnsa on 2020-01-19.
//
#include "ESParser.h"
#include "MacroblockModesParser.h"
#include "../../VideoDecoder/VideoDecoder.h"


#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

MacroblockModesParser::vlc MacroblockModesParser::table_b2[] = {
        {0, 0, 0, 0, 1, 0, 0, 1, 0b1},
        {1, 0, 0, 0, 1, 0, 0, 2, 0b01}
};
size_t MacroblockModesParser::table_b2_size = 2;
MacroblockModesParser::vlc MacroblockModesParser::table_b3[] = {
        {0, 1, 0, 1, 0, 0, 0, 1, 0b1},
        {0, 0, 0, 1, 0, 0, 0, 2, 0b01},
        {0, 1, 0, 0, 0, 0, 0, 3, 0b001},
        {0, 0, 0, 0, 1, 0, 0, 5, 0b00011},
        {1, 1, 0, 1, 0, 0, 0, 5, 0b00010},
        {1, 0, 0, 1, 0, 0, 0, 5, 0b00001},
        {1, 0, 0, 0, 1, 0, 0, 6, 0b000001}
};
size_t MacroblockModesParser::table_b3_size = 7;
MacroblockModesParser::vlc MacroblockModesParser::table_b4[] = {
        {0, 1, 1, 0, 0, 0, 0, 2, 0b10},
        {0, 1, 1, 1, 0, 0, 0, 2, 0b11},
        {0, 0, 1, 0, 0, 0, 0, 3, 0b010},
        {0, 0, 1, 1, 0, 0, 0, 3, 0b011},
        {0, 1, 0, 0, 0, 0, 0, 4, 0b0010},
        {0, 1, 0, 1, 0, 0, 0, 4, 0b0011},
        {0, 0, 0, 0, 1, 0, 0, 5, 0b00011},
        {1, 1, 1, 1, 0, 0, 0, 5, 0b00010},
        {1, 1, 0, 1, 0, 0, 0, 6, 0b000011},
        {1, 0, 1, 1, 0, 0, 0, 6, 0b000010},
        {1, 0, 0, 0, 1, 0, 0, 6, 0b000001}
};
size_t MacroblockModesParser::table_b4_size = 11;

MacroblockModes *MacroblockModesParser::macroblock_modes() {
    PictureDecoder *pictureDecoder = VideoDecoder::getInstance()->getPictureDecoder();
    MacroblockModes::initializerStruct init = {};
    decodeMacroblockType(&init);
    //spatial_temporal_weight_code would be decoded here but is not handled
    if (init.macroblock_motion_forward || init.macroblock_motion_backward) {
        if (pictureDecoder->getPictureStructure() == PictureCodingExtensionPacket::picture_structure_types::frame) {
            if (!pictureDecoder->isFramePredFrameDct()) {
                init.frame_motion_type = (unsigned char) read(2);
            }
        } else {
            init.field_motion_type = (unsigned char) read(2);
        }
    }
    if (pictureDecoder->getPictureStructure() == PictureCodingExtensionPacket::picture_structure_types::frame &&
        !pictureDecoder->isFramePredFrameDct() && (init.macroblock_intra || init.macroblock_pattern)) {
        init.dct_type = (bool) read(1);
    }
    if (pictureDecoder->isFramePredFrameDct() || pictureDecoder->isConcealmentMotionVectors()) {
        init.frame_motion_type = 0b10;
    }
    if (pictureDecoder->isConcealmentMotionVectors()) {
        init.field_motion_type = 0b01;
    }
    if (!init.macroblock_intra) {
        pictureDecoder->resetDctDcPred(); // reset dct_dc_pred as per Table 7-2
    }
    return new MacroblockModes(init);
}

void MacroblockModesParser::decodeMacroblockType(MacroblockModes::initializerStruct *init) {
    vlc *table;
    size_t size;
    switch (VideoDecoder::getInstance()->getPictureDecoder()->getPictureCodingType()) {
        case PictureHeaderPacket::picture_coding_types::intra_coded:
            table = table_b2;
            size = table_b2_size;
            break;
        case PictureHeaderPacket::picture_coding_types::predictive_coded:
            table = table_b3;
            size = table_b3_size;
            break;
        case PictureHeaderPacket::picture_coding_types::bidirectionally_predictive_coded:
            table = table_b4;
            size = table_b4_size;
            break;
        case PictureHeaderPacket::picture_coding_types::reserved_forbidden:
            throw PacketException("MacroblockModesParser::decodeMacroblockType: Unexpected picture coding type\n");
    }
    for (int i = 0; i < size; i++) {
        vlc code = table[i];
        if (peek(code.numBits) == code.key) {
            read(code.numBits);
            init->macroblock_quant = code.macroblock_quant;
            init->macroblock_motion_forward = code.macroblock_motion_forward;
            init->macroblock_motion_backward = code.macroblock_motion_backward;
            init->macroblock_pattern = code.macroblock_pattern;
            init->macroblock_intra = code.macroblock_intra;
            init->spatial_temporal_weight_code_flag = code.spatial_temporal_weight_code_flag;
            if (code.spatial_temporal_weight_code_flag == 1) {
                throw PacketException(
                        "MacroblockModesParser::decodeMacroblockType: spatial_temporal_weight_code_flag == 1 is not handled by the decoder\n");
            }
            init->spatial_temporal_weight_classes = code.spatial_temporal_weight_classes;
            return;
        }
    }
    throw PacketException("MacroblockModesParser::decodeMacroblockTypeHelper: Unexpected vlc code\n");
}

#pragma clang diagnostic pop