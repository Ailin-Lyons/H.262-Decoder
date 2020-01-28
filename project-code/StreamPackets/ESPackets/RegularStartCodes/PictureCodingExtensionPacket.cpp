//
// Created by elnsa on 2020-01-16.
//

#include "PictureCodingExtensionPacket.h"

PictureCodingExtensionPacket::PictureCodingExtensionPacket(PictureCodingExtensionPacket::initializerStruct init) {
    packet_type = ESPacket::start_code::extension;
    stream_id = 0xB5;
    e_type = ExtensionPacket::extension_type::picture_coding;
    f_code_0_0 = init.f_code_0_0;
    f_code_0_1 = init.f_code_0_1;
    f_code_1_0 = init.f_code_1_0;
    f_code_1_1 = init.f_code_1_1;
    intra_dc_precision = init.intra_dc_precision;
    picture_structure = init.picture_structure;
    top_field_first = init.top_field_first;
    frame_pred_frame_dct = init.frame_pred_frame_dct;
    concealment_motion_vectors = init.concealment_motion_vectors;
    q_scale_type = init.q_scale_type;
    intra_vlc_format = init.intra_vlc_format;
    alternate_scan = init.alternate_scan;
    repeat_first_field = init.repeat_first_field;
    chroma_420_type = init.chroma_420_type;
    progressive_frame = init.progressive_frame;
    composite_display_flag = init.composite_display_flag;
    v_axis = init.top_field_first;
    field_sequence = init.frame_pred_frame_dct;
    sub_carrier = init.concealment_motion_vectors;
    burst_amplitude = init.q_scale_type;
    sub_carrier_phase = init.intra_vlc_format;
}

PictureCodingExtensionPacket::intra_dc_precision_bits
PictureCodingExtensionPacket::getIntraDCPrecisionType(unsigned char i_dc_p) {
    switch (i_dc_p) {
        case 0b00:
            return intra_dc_precision_bits::p_8;
        case 0b01:
            return intra_dc_precision_bits::p_9;
        case 0b10:
            return intra_dc_precision_bits::p_10;
        case 0b11:
            return intra_dc_precision_bits::p_11;
        default:
            throw PacketException("PictureCodingExtensionPacket::getIntraDCPrecisionType: illegal value\n");
    }
}

PictureCodingExtensionPacket::picture_structure_types
PictureCodingExtensionPacket::getPictureStructureType(unsigned char pictureStructure) {
    switch (pictureStructure) {
        case 0b00:
            return picture_structure_types::ps_reserved;
        case 0b01:
            return picture_structure_types::ps_top_field;
        case 0b10:
            return picture_structure_types::ps_bottom_field;
        case 0b11:
            return picture_structure_types::frame;
        default:
            throw PacketException("PictureCodingExtensionPacket::getPictureStructureType: illegal value\n");
    }
}

void PictureCodingExtensionPacket::print() {
    printf("PictureCodingExtensionPacket::print TODO\n");
}

bool PictureCodingExtensionPacket::operator==(const PictureCodingExtensionPacket &rhs) const {
    return f_code_0_0 == rhs.f_code_0_0 &&
           f_code_0_1 == rhs.f_code_0_1 &&
           f_code_1_0 == rhs.f_code_1_0 &&
           f_code_1_1 == rhs.f_code_1_1 &&
           intra_dc_precision == rhs.intra_dc_precision &&
           picture_structure == rhs.picture_structure &&
           top_field_first == rhs.top_field_first &&
           frame_pred_frame_dct == rhs.frame_pred_frame_dct &&
           concealment_motion_vectors == rhs.concealment_motion_vectors &&
           q_scale_type == rhs.q_scale_type &&
           intra_vlc_format == rhs.intra_vlc_format &&
           alternate_scan == rhs.alternate_scan &&
           repeat_first_field == rhs.repeat_first_field &&
           chroma_420_type == rhs.chroma_420_type &&
           progressive_frame == rhs.progressive_frame &&
           composite_display_flag == rhs.composite_display_flag &&
           v_axis == rhs.v_axis &&
           field_sequence == rhs.field_sequence &&
           sub_carrier == rhs.sub_carrier &&
           burst_amplitude == rhs.burst_amplitude &&
           sub_carrier_phase == rhs.sub_carrier_phase;
}

bool PictureCodingExtensionPacket::operator!=(const PictureCodingExtensionPacket &rhs) const {
    return !(rhs == *this);
}

unsigned char PictureCodingExtensionPacket::getFCode00() const {
    return f_code_0_0;
}

unsigned char PictureCodingExtensionPacket::getFCode01() const {
    return f_code_0_1;
}

unsigned char PictureCodingExtensionPacket::getFCode10() const {
    return f_code_1_0;
}

unsigned char PictureCodingExtensionPacket::getFCode11() const {
    return f_code_1_1;
}

PictureCodingExtensionPacket::intra_dc_precision_bits PictureCodingExtensionPacket::getIntraDcPrecision() const {
    return intra_dc_precision;
}

PictureCodingExtensionPacket::picture_structure_types PictureCodingExtensionPacket::getPictureStructure() const {
    return picture_structure;
}

bool PictureCodingExtensionPacket::isTopFieldFirst() const {
    return top_field_first;
}

bool PictureCodingExtensionPacket::isFramePredFrameDct() const {
    return frame_pred_frame_dct;
}

bool PictureCodingExtensionPacket::isConcealmentMotionVectors() const {
    return concealment_motion_vectors;
}

bool PictureCodingExtensionPacket::isQScaleType() const {
    return q_scale_type;
}

bool PictureCodingExtensionPacket::isIntraVlcFormat() const {
    return intra_vlc_format;
}

bool PictureCodingExtensionPacket::isAlternateScan() const {
    return alternate_scan;
}

bool PictureCodingExtensionPacket::isRepeatFirstField() const {
    return repeat_first_field;
}

bool PictureCodingExtensionPacket::isChroma420Type() const {
    return chroma_420_type;
}

bool PictureCodingExtensionPacket::isProgressiveFrame() const {
    return progressive_frame;
}

bool PictureCodingExtensionPacket::isCompositeDisplayFlag() const {
    return composite_display_flag;
}
