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
    progressive_frame = init.intra_dc_precision;
    composite_display_flag = init.picture_structure;
    v_axis = init.top_field_first;
    field_sequence = init.frame_pred_frame_dct;
    sub_carrier = init.concealment_motion_vectors;
    burst_amplitude = init.q_scale_type;
    sub_carrier_phase = init.intra_vlc_format;
}

void PictureCodingExtensionPacket::print() {
    printf("PictureCodingExtensionPacket::print TODO");
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
