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

void ESParser::loadNextTSPacket() {
    if (nextTP != 0) {
        currTP = nextTP;
        nextTP = 0;
    } else {
        currTP = TSParser::getNextPacket();
    }
    currPos = currTP->data;
    currOffset = 0;
    endPos = currTP->data + currTP->data_length;
}

void ESParser::next_start_code() {
    while (!bytealigned()) {
        popNBits(1);
    }
    while (peekNBits(24) != 0x000001) {
        popNBits(8);
    }
    popNBits(24); //
}

bool ESParser::bytealigned() {
    return currOffset == 0;
}

void ESParser::findNextValidPacket() {
    next_start_code();
    unsigned char stream_id = peekNBits(8);
    ESPacket::start_code packet_type = ESPacket::getStartCode(stream_id);
    if (ESPacket::isHandled(packet_type)) {
        return;
    }
    std::printf("Unhandled PESPacket has been dropped: %x\n",stream_id);
    return findNextValidPacket();
}

ESPacket *ESParser::getNextPacket() {
    findNextValidPacket();
    unsigned char stream_id = popNBits(8);
    ESPacket::start_code packet_type = ESPacket::getStartCode(stream_id);
    std::printf("PESPacket code: %x\n",stream_id);
    if (isVideoStream) {
        return getNextVideoPacket(packet_type, stream_id);
    } else {
        //TODO call PESPacketParser here and create PESPacket
        //TODO update ESParser::currVideoStreamID if necessary
        return nullptr;
    }
}

unsigned long long ESParser::peekNBits(unsigned int numBits) {
    if (numBits > 64) throw PacketException("ESParser::peekNBits: requesting too many bytes");
    if (numBits < numBitsRemaining()) {
        return BitManipulator::readNBitsOffset(currPos, currOffset, numBits);
    } else {
        unsigned int part1 = numBitsRemaining();
        unsigned int part2 = numBits - part1;
        unsigned long long out = BitManipulator::readNBitsOffset(currPos, currOffset, part1);
        return (out << part2) + peekNextPacket(part2);
    }
}

unsigned long long ESParser::popNBits(unsigned int numBits) {
    if (numBits > 64) throw PacketException("ESParser::popNBits: requesting too many bytes");
    if (numBits < numBitsRemaining()) {
        unsigned long long out = BitManipulator::readNBitsOffset(currPos, currOffset, numBits);
        incrementOffset(numBits);
        return out;
    } else if (numBits == numBitsRemaining()) {
        unsigned long long out = BitManipulator::readNBitsOffset(currPos, currOffset, numBits);
        loadNextTSPacket();
        return out;
    } else {
        unsigned int part1 = numBitsRemaining();
        unsigned int part2 = numBits - part1;
        unsigned long long out = BitManipulator::readNBitsOffset(currPos, currOffset, part1);
        loadNextTSPacket();
        if (numBits > (currTP->data_length * 8)) {
            throw PacketException("ESParser::popNBits: next packet is too short");
        }
        out = (out << part2) + BitManipulator::readNBitsOffset(currPos, currOffset, part2);
        incrementOffset(part2);
        return out;
    }
}

unsigned int ESParser::numBitsRemaining() {
    return (endPos - currPos) * 8 - currOffset;
}

unsigned long long ESParser::peekNextPacket(unsigned int numBits) {
    if (nextTP == 0) {
        nextTP = TSParser::getNextPacket();
    }
    if (numBits > (nextTP->data_length * 8)) {
        nextTP->toString();
        throw PacketException("ESParser::peekNextPacket: next packet is too short");
    }
    return BitManipulator::readNBits(nextTP->data, numBits);
}

void ESParser::incrementOffset(unsigned int numBits) {
    if (currOffset != 0) {
        numBits -= (8 - currOffset);
        currPos++;
    }
    currPos += (numBits / 8);
    currOffset = numBits % 8;
}
