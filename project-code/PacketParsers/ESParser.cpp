#include "ESParser.h"

//
// Created by elnsa on 2019-12-23.
//

// Linker needs to know where to allocate memory for the static instance
ESParser *ESParser::instance = nullptr;

ESParser::ESParser() {
    loadNextTSPacket();
    isVideoStream = false;
    currVideoStreamID = 0;
}

ESPacket *ESParser::getNextVideoPacket(ESPacket::start_code scode, unsigned char stream_id) {
    switch (scode) {
        case ESPacket::start_code::picture:
            return nullptr;//TODO
        case ESPacket::start_code::slice:
            return nullptr;//TODO
        case ESPacket::start_code::sequence_header:
            return nullptr;//TODO
        case ESPacket::start_code::extension:
            return nullptr;//TODO
        case ESPacket::start_code::group:
            return nullptr;//TODO
        default:
            throw PacketException("ESParser::getNextVideoPacket:: Invalid Packet type");
    }
}

/**
 * Request the next TSPacket from TSParser and initiates currPos and endPos to wrap around this TSPackets data
 */
void ESParser::loadNextTSPacket() {
    currTP = TSParser::GetNextPacket();
    currPos = currTP->data;
    endPos = currTP->data + currTP->data_length;
}

void ESParser::findNextStartCode() {
    if (currPos + 4 >= endPos) {
        loadNextTSPacket();
        return findNextStartCode();
    } else {
        if (BitManipulator::ReadNBits(currPos, 24) == 0x000001) {
            currPos += 3;
            return;
        }
        currPos++;
        return findNextStartCode();
    }
}

void ESParser::findNextValidPacket() {
    findNextStartCode();
    unsigned char stream_id = BitManipulator::ReadNBits(currPos, 8);
    ESPacket::start_code packet_type = ESPacket::GetStartCode(stream_id);
    if (ESPacket::IsHandled(packet_type)) {
        return;
    }
    currPos += 1;
    return findNextValidPacket();
}

/**
 * Returns the next elementary stream packet if it
 * Ignores any packets not handled by this decoder.
 * @return one of many possible packets that implements the ESPacket interface.
 */
ESPacket *ESParser::getNextPacket() {
    findNextValidPacket();
    unsigned char stream_id = BitManipulator::ReadNBits(currPos, 8);
    currPos++;
    ESPacket::start_code packet_type = ESPacket::GetStartCode(stream_id);
    if (isVideoStream) {
        return getNextVideoPacket(packet_type, stream_id);
    } else {
        //TODO call PESPacketParser here and create PESPacket
//        unsigned short PES_packet_length = BitManipulator::ReadNBits(currPos, 16);
//        currPos += 2;
        return nullptr;
    }
}
