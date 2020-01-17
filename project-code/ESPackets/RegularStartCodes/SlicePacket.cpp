//
// Created by elnsa on 2019-12-29.
//

#include "SlicePacket.h"

SlicePacket::SlicePacket(SlicePacket::initializerStruct init) {
    stream_id = init.stream_id;
    packet_type = ESPacket::start_code::slice;
    slice_start_code = init.slice_start_code;
    slice_vertical_position_extension = init.slice_vertical_position_extension;
    priority_breakpoint = init.priority_breakpoint;
    quantiser_scale_code = init.quantiser_scale_code;
    slice_extension_flag = init.slice_extension_flag;
    intra_slice = init.intra_slice;
    slice_picture_id_enable = init.slice_picture_id_enable;
    slice_picture_id = init.slice_picture_id;
    numExtraInfo  = init.numExtraInfo;
    extra_Information = init.extra_Information;
    extra_bit_slice = init.extra_bit_slice;
}

void SlicePacket::print() {
    std::printf("stream_id = %hhu\npacket_type = ESPacket::start_code::slice\nslice_start_code = %u\n"
                "slice_vertical_position_extension = %hhu\npriority_breakpoint = %hhu\nquantiser_scale_code = %hhu\n"
                "slice_extension_flag = %hhu\nintra_slice = %hhu\nslice_picture_id_enable = %hhu\n"
                "slice_picture_id = %hhu\nnumExtraInfo = %u\nExtra_Information : %p\n", stream_id, slice_start_code,
                slice_vertical_position_extension, priority_breakpoint, quantiser_scale_code, slice_extension_flag,
                intra_slice, slice_picture_id_enable, slice_picture_id, numExtraInfo, extra_Information);
    for (size_t i = 0; i < numExtraInfo; i++) {
        std::printf("\tExtra_Information[%u]:\n\t\textra_bit_slice = %hhu, extra_information_slice = %hhu\n", i,
                extra_Information[i].extra_bit_slice, extra_Information[i].extra_information_slice);
    }
    std::printf("extra_bit_slice = %hhu", extra_bit_slice);
}

bool SlicePacket::operator==(const SlicePacket &rhs) const {
    bool ret = stream_id == rhs.stream_id && packet_type == rhs.packet_type && slice_start_code == rhs.slice_start_code
            && slice_vertical_position_extension == rhs.slice_vertical_position_extension &&
            priority_breakpoint == rhs.priority_breakpoint && quantiser_scale_code == rhs.quantiser_scale_code &&
            slice_extension_flag == rhs.slice_extension_flag && intra_slice == rhs.intra_slice &&
            slice_picture_id_enable == rhs.slice_picture_id && slice_picture_id == rhs.slice_picture_id &&
            numExtraInfo  == rhs.numExtraInfo && extra_bit_slice == rhs.extra_bit_slice;
    size_t i = 0;
    while (ret && i < numExtraInfo) {
        ret = ret && extra_Information[i].extra_bit_slice == rhs.extra_Information[i].extra_bit_slice &&
                extra_Information[i].extra_information_slice && rhs.extra_Information[i].extra_information_slice;
        i++;
    }
    return ret;
}

bool SlicePacket::operator!=(const SlicePacket &rhs) const {
    return !(rhs == *this);
}

SlicePacket::~SlicePacket() {
    free(extra_Information);
}
