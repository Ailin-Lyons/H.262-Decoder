//
// Created by elnsa on 2019-12-29.
//

#include "GroupOfPicturesHeaderPacket.h"

GroupOfPicturesHeaderPacket::GroupOfPicturesHeaderPacket(GroupOfPicturesHeaderPacket::initializerStruct init) {
    group_start_code = init.group_start_code;
    time_code = init.time_code;
    closed_gop = init.closed_gop;
    broken_link = init.broken_link;
}

void GroupOfPicturesHeaderPacket::print() {
    std::printf("GroupOfPicturesHeaderPacket: gsc %x, tc %x, cgop %x, bl %x.\n",
                group_start_code, time_code, closed_gop, broken_link);
}

bool GroupOfPicturesHeaderPacket::operator==(const GroupOfPicturesHeaderPacket &rhs) const {
    return group_start_code == rhs.group_start_code &&
           time_code == rhs.time_code &&
           closed_gop == rhs.closed_gop &&
           broken_link == rhs.broken_link;
}

bool GroupOfPicturesHeaderPacket::operator!=(const GroupOfPicturesHeaderPacket &rhs) const {
    return !(rhs == *this);
}
