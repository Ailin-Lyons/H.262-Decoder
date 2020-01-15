//
// Created by elnsa on 2019-12-29.
//

#include "PictureHeaderPacket.h"

PictureHeaderPacket::PictureHeaderPacket(PictureHeaderPacket::initializerStruct init) {
    picture_start_code = init.picture_start_code;
    temporal_reference = init.temporal_reference;
    picture_coding_type = init.picture_coding_type;
    vbv_delay = init.vbv_delay;
}

void PictureHeaderPacket::print() {
    std::printf("PictureHeaderPacket: psc %x, tr %x, pct %x, vbvd %x.\n",
                picture_start_code, temporal_reference, picture_coding_type, vbv_delay);
}

bool PictureHeaderPacket::operator==(const PictureHeaderPacket &rhs) const {
    return picture_start_code == rhs.picture_start_code &&
           temporal_reference == rhs.temporal_reference &&
           picture_coding_type == rhs.picture_coding_type &&
           vbv_delay == rhs.vbv_delay;
}

bool PictureHeaderPacket::operator!=(const PictureHeaderPacket &rhs) const {
    return !(rhs == *this);
}
