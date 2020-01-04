#include "ESParser.h"

//
// Created by elnsa on 2019-12-23.
//
ESParser::ESParser() {
    currTP = TSParser::GetNextPacket();
    currPos = currTP->data;
    endPos = currTP->data + currTP->data_length;
    isVideoStream = false;
    currVideoStreamID = 0;
}

/**
 * Returns the next elementary stream packet if it exists //TODO this entire function needs to be rewritten to contain state machine
 * Ignores any packets not handled by this decoder.
 * @param tp a pointer to a valid TransportPacket
 * @return a struct of type pes_packet_array that contains num_packets PESPacket* in packet_array
 * Caller is responsible for freeing each PESPacket as well as packet_array
 */
ESPacket *ESParser::GetNextPacket() {
    if (currPos + 4 >= endPos) {
        //TODO throw error? not enough bytes left in packet
        throw;
    }
    unsigned int packet_start_code_prefix = BitManipulator::ReadNBits(currPos, 24);
    currPos += 3;
    if (packet_start_code_prefix != 0x000001) {
        throw PacketException("ESParser::Invalid packet_start_code_prefix!");
        // We may want to deliberately clean out stuffing bytes in future
    }
    unsigned char stream_id = BitManipulator::ReadNBits(currPos, 8);
    currPos++;
    ESPacket::start_code packet_type = ESPacket::GetStartCode(stream_id);
    if (!ESPacket::IsHandled(packet_type)) {
        return ESParser::GetNextPacket();
    }
    if (isVideoStream) {
        return ESParser::GetNextVideoPacket(packet_type, stream_id);
    } else {

        unsigned short PES_packet_length = BitManipulator::ReadNBits(currPos, 16);
        currPos += 2;
        if (currPos + PES_packet_length <= endPos && ESPacket::IsHandled(packet_type)) {
            return nullptr; //TODO call 262 Parser class and return ESPacket
        }
    }
}

PESPacket *GetNextVideoPacket(ESPacket::start_code scode, unsigned char stream_id) {
    switch (scode) {
        case ESPacket::start_code::picture:
            //TODO
        case ESPacket::start_code::slice:
            //TODO
        case ESPacket::start_code::sequence_header:
            //TODO
        case ESPacket::start_code::extension:
            //TODO
        case ESPacket::start_code::group:
            //TODO
        default:
            throw PacketException("ESParser::GetNextVideoPacket:: Invalid Packet type");
    }
    throw; //TODO
}

