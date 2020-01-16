//
// Created by elnsa on 2019-12-29.
//

#include "SlicePacket.h"

SlicePacket::SlicePacket(SlicePacket::initializerStruct init) {
    stream_id = init.stream_id;
    packet_type = ESPacket::start_code::slice;
}

void SlicePacket::print() {

}

bool SlicePacket::operator==(const SlicePacket &rhs) const {
    return false;
}

bool SlicePacket::operator!=(const SlicePacket &rhs) const {
    return false;
}

SlicePacket::~SlicePacket() {

}
