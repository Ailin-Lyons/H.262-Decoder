//
// Created by elnsa on 2019-12-29.
//

#include "PictureHeaderPacket.h"

PictureHeaderPacket::PictureHeaderPacket(PictureHeaderPacket::initializerStruct init) {
    packet_type = ESPacket::start_code::picture;
    stream_id = 0x00;
    temporal_reference = init.temporal_reference;
    picture_coding_type = init.picture_coding_type;
    vbv_delay = init.vbv_delay;
}

void PictureHeaderPacket::print() {
    printf("PictureHeaderPacket: temporal_reference %x, picture_coding_types %x, vbv_delay %x.\n",
           temporal_reference, picture_coding_type, vbv_delay);
}

bool PictureHeaderPacket::operator==(const PictureHeaderPacket &rhs) const {
    return temporal_reference == rhs.temporal_reference &&
           picture_coding_type == rhs.picture_coding_type &&
           vbv_delay == rhs.vbv_delay;
}

bool PictureHeaderPacket::operator!=(const PictureHeaderPacket &rhs) const {
    return !(rhs == *this);
}

unsigned short PictureHeaderPacket::getTemporalReference() const {
    return temporal_reference;
}

PictureHeaderPacket::picture_coding_types PictureHeaderPacket::getPictureCodingType() const {
    return picture_coding_type;
}

std::string PictureHeaderPacket::getPictureCodingTypeString() const {
    switch (picture_coding_type) {
        default:
            return "wrong picture type";
        case picture_coding_types::intra_coded :
            return "intra_coded (I-frames)";
        case picture_coding_types::predictive_coded :
            return "predictive_coded (P-frames)";
        case picture_coding_types::bidirectionally_predictive_coded :
            return "bidirectionally_predictive_coded (I-frames)";
    }
}

PictureHeaderPacket::picture_coding_types PictureHeaderPacket::toPictureCodingType(unsigned char x) {
    switch (x) {
        default:
            return PictureHeaderPacket::picture_coding_types::reserved_forbidden;
        case 1:
            return PictureHeaderPacket::picture_coding_types::intra_coded;
        case 2:
            return PictureHeaderPacket::picture_coding_types::predictive_coded;
        case 3:
            return PictureHeaderPacket::picture_coding_types::bidirectionally_predictive_coded;
    }
}
