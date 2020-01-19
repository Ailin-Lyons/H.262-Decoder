//
// Created by elnsa on 2020-01-18.
//

#include "PictureDecoder.h"

void PictureDecoder::setClosedGop(bool closedGop) {
    closed_gop = closedGop;
}

void PictureDecoder::setBrokenLink(bool brokenLink) {
    broken_link = brokenLink;
}

void PictureDecoder::setTemporalReference(unsigned short temporalReference) {
    temporal_reference = temporalReference;
}

void PictureDecoder::setPictureCodingType(PictureHeaderPacket::picture_coding_types pictureCodingType) {
    picture_coding_type = pictureCodingType;
}
