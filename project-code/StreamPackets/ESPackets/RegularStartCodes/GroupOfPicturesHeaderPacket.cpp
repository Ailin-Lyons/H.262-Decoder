//
// Created by elnsa on 2019-12-29.
//

#include "GroupOfPicturesHeaderPacket.h"

GroupOfPicturesHeaderPacket::GroupOfPicturesHeaderPacket(GroupOfPicturesHeaderPacket::initializerStruct init) {
    packet_type = ESPacket::start_code::group;
    stream_id = 0xB8;
    time_code = init.time_code;
    closed_gop = init.closed_gop;
    broken_link = init.broken_link;
}

void GroupOfPicturesHeaderPacket::print() {
    printf("GroupOfPicturesHeaderPacket: time_code %x, closed_gop %x, broken_link %x.\n", time_code, closed_gop, broken_link);
}

bool GroupOfPicturesHeaderPacket::operator==(const GroupOfPicturesHeaderPacket &rhs) const {
    return time_code == rhs.time_code &&
           closed_gop == rhs.closed_gop &&
           broken_link == rhs.broken_link;
}

bool GroupOfPicturesHeaderPacket::operator!=(const GroupOfPicturesHeaderPacket &rhs) const {
    return !(rhs == *this);
}

bool GroupOfPicturesHeaderPacket::isClosedGop() const {
    return closed_gop;
}

bool GroupOfPicturesHeaderPacket::isBrokenLink() const {
    return broken_link;
}
