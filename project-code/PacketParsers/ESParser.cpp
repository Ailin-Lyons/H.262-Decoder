#include "ESParser.h"
#include "PASParser.cpp"
#include "PMSParser.cpp"
#include "../TSPayloadSections/ProgramAssociationSection.h"
#include "ESPacketParsers/GroupHeaderParser.cpp"
#include "ESPacketParsers/PictureHeaderParser.cpp"
#include "ESPacketParsers/SequenceExtensionParser.cpp"
#include "ESPacketParsers/SequenceHeaderParser.cpp"
#include "ESPacketParsers/SliceParser.cpp"
#include "PESParser.cpp"


//
// Created by elnsa on 2019-12-23.
//

// Linker needs to know where to allocate memory for the static instance
ESParser *ESParser::instance = nullptr;

ESParser::ESParser() {
    currOffset = 0;
}

void ESParser::initiateStream() {
    nextTP = nullptr;
    program_pid = 0x00;
    loadNextTSPacket();
    programAssociationSection = PASParser::getPASPacket();
    std::printf("\t***Loaded PAS: program_1 PID is %x ***\n", programAssociationSection->getProgramPID());
    program_pid = programAssociationSection->getProgramPID();
    loadNextTSPacket();
    programMapSection = PMSParser::getPMSPacket();
    std::printf("\t***Loaded PMS for PID %x: video_stream PID is %x ***\n", programAssociationSection->getProgramPID(),
                programMapSection->getVideoStreamPID());
    program_pid = programMapSection->getVideoStreamPID();
    loadNextTSPacket();
}

void ESParser::loadNextTSPacket() {
    if (nextTP != nullptr) {
        currTP = nextTP;
        nextTP = nullptr;
    } else {
        currTP = findNextTSPacket();
    }
    currPos = currTP->getData();
    currOffset = 0;
    endPos = currTP->getData() + currTP->getDataLength();
}

void ESParser::next_start_code() {
    while (!bytealigned()) {
        popNBits(1);
    }
    while (peekNBits(24) != 0x000001) {
        popNBits(8);
    }
}

bool ESParser::bytealigned() {
    return currOffset == 0;
}

unsigned char ESParser::nextESPacketID() {
    unsigned char stream_id = peekNBits(8);
    ESPacket::start_code packet_type = ESPacket::getStartCode(stream_id);
    if (ESPacket::isHandled(packet_type)) {
        return stream_id;
    }
    std::printf("Unhandled PESPacket has been dropped: %x\n", stream_id);
    return nextESPacketID();
}

ESPacket *ESParser::getNextPacket() {
    next_start_code();
    if (popNBits(24) != 0x000001) {
        throw PacketException("ESParser::getNextPacket() missing start_code\n");
    }
    unsigned char stream_id = popNBits(8);
    ESPacket::start_code packet_type = ESPacket::getStartCode(stream_id);
    std::printf("PESPacket code: %x\n", stream_id);
    switch (packet_type) {
        case ESPacket::start_code::video_stream:
            return PESParser::getNextPesPacket(packet_type);
        case ESPacket::start_code::picture:
            return PictureHeaderParser::getNextPacket();
        case ESPacket::start_code::slice:
            return SliceParser::getNextPacket(stream_id);
        case ESPacket::start_code::sequence_header:
            return SequenceHeaderParser::getNextPacket();
        case ESPacket::start_code::extension:
            return getExtensionPacket();
        case ESPacket::start_code::group:
            return GroupHeaderParser::getNextPacket();
        default:
            throw PacketException("ESParser::getNextVideoPacket:: Invalid Packet type\n");
    }
}

unsigned long long ESParser::peekNBits(unsigned int numBits) {
    if (numBits > 64) throw PacketException("ESParser::peekNBits: requesting too many bytes");
    if (numBits <= numBitsRemaining()) {
        return BitManipulator::readNBitsOffset(currPos, currOffset, numBits);
    } else {
        unsigned int part1 = numBitsRemaining();
        unsigned int part2 = numBits - part1;
        unsigned long long out = BitManipulator::readNBitsOffset(currPos, currOffset, part1);
        out = (out << part2) + peekNextPacket(part2);
        return out;
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
        incrementOffset(numBits);
        return out;
    } else {
        unsigned int part1 = numBitsRemaining();
        unsigned int part2 = numBits - part1;
        unsigned long long out = BitManipulator::readNBitsOffset(currPos, currOffset, part1);
        loadNextTSPacket();
        if (numBits > (currTP->getDataLength() * 8)) {
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
    if (nextTP == nullptr) {
        nextTP = findNextTSPacket();
    }
    if (numBits > (nextTP->getDataLength() * 8)) {
        nextTP->print();
        throw PacketException("ESParser::peekNextPacket: next packet is too short");
    }
    return BitManipulator::readNBits(nextTP->getData(), numBits);
}

void ESParser::incrementOffset(unsigned int numBits) {
    while (numBits > 0 && currOffset != 0) {
        numBits--;
        currOffset++;
        if (currOffset == 8) {
            currOffset = 0;
            currPos++;
        }
    }
    currPos += (numBits / 8);
    if (numBits != 0) {
        currOffset = numBits % 8;
    }
}

TransportPacket *ESParser::findNextTSPacket() {
    TransportPacket *out = TSParser::getNextPacket();
    while (out->getPacketPID() != program_pid) {
        std::printf("\tDiscarded TSPacket with pid: %x\n", out->getPacketPID());
        out = TSParser::getNextPacket();
    }
    return out;
}

ESPacket *ESParser::getExtensionPacket() {
    unsigned char extension_start_code_identifier = popNBits(4);
    ESPacket::extension_type e_type = ESPacket::getExtensionCode(extension_start_code_identifier);
    switch (e_type) {
        case ESPacket::extension_type::sequence:
            return SequenceExtensionParser::getNextPacket(extension_start_code_identifier);
        case ESPacket::extension_type::sequence_display:
            std::printf("TODO extension sequence_display\n");
            return nullptr; //TODO implement
        case ESPacket::extension_type::picture_coding:
            std::printf("TODO extension picture_coding\n");
            return nullptr; //TODO implement
        default:
            throw PacketException("ESParser::Unhandled extension_start_code_identifier\n");
    }
}
