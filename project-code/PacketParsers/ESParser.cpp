#include "ESParser.h"

//
// Created by elnsa on 2019-12-23.
//

    // Linker needs to know where to allocate memory for the static instance
    ESParser *ESParser::instance = nullptr;

    ESParser::ESParser() {
        currTP = TSParser::GetNextPacket();
        currPos = currTP->data;
        endPos = currTP->data + currTP->data_length;
        isVideoStream = false;
        currVideoStreamID = 0;
    }


    /**
     * Returns the next elementary stream packet if it exists
     * Ignores any packets not handled by this decoder.
     * @param tp a pointer to a valid TransportPacket
     * @return a struct of type pes_packet_array that contains num_packets PESPacket* in packet_array
     * Caller is responsible for freeing each PESPacket as well as packet_array
     */
    ESPacket* ESParser::GetNextPacket() {
        if (isVideoStream) {
            //TODO this branch
        } else {
            if (currPos + 4 >= endPos) {
                //TODO throw error? not enough bytes left in packet
            }
        }
        //    if (currPos + 5 < endPos) {
        //        unsigned int packet_start_code_prefix = BitManipulator::ReadNBits(currPos, 24);
        //        currPos += 3;
        //        if (packet_start_code_prefix != 0x000001) {
        //            throw PacketException("ESParser::Invalid packet_start_code_prefix!");
        //            // We may want to deliberatly clean out stuffing bytes in future
        //        }
        //        unsigned char stream_id = BitManipulator::ReadNBits(currPos, 8);
        //        currPos++;
        //        ESPacket::start_code packet_type = ESPacket::GetStartCode(stream_id);
        //        unsigned short PES_packet_length = BitManipulator::ReadNBits(currPos, 16);
        //        currPos += 2;
        //        if (currPos + PES_packet_length <= endPos && ESPacket::IsHandled(packet_type)) {
        //            tempArray[numPackets] = GetNextPacket(packet_type, stream_id, PES_packet_length, currPos);
        //            numPackets++;
        //            if (numPackets > MAXPACKETS) {
        //                throw PacketException("ESParser::MAXPACKETS exceeded!");
        //            }
        //        }
        //    }
        //    out.num_packets = numPackets;
        //    out.packet_array = (PESPacket **) malloc(sizeof(PESPacket * ) * numPackets);
        //    for (int i = 0; i < numPackets; i++) {
        //        out.packet_array[i] = tempArray[i];
        //    }
        //    return out;
        return nullptr;
    }

    TransportPacket *ESParser::giveNextPacket() {
        return nullptr; // TODO implement
    }


    static PESPacket *GetPESPicture(unsigned char id, unsigned short length, unsigned char *start_pos) {
        return nullptr; // TODO implement
    }

    static PESPacket *GetPESSlice(unsigned char id, unsigned short length, unsigned char *start_pos) {
        return nullptr; // TODO implement
    }

    static PESPacket *GetPESSequenceHeader(unsigned char id, unsigned short length, unsigned char *start_pos) {
        return nullptr; // TODO implement
    }

    static PESPacket *GetPESExtension(unsigned char id, unsigned short length, unsigned char *start_pos) {
        return nullptr; // TODO implement
    }

    static PESPacket *GetPESGroup(unsigned char id, unsigned short length, unsigned char *start_pos) {
        return nullptr; // TODO implement
    }

    static PESPacket *GetPESVideoStream(unsigned char id, unsigned short length, unsigned char *start_pos) {
        return nullptr; // TODO implement
    }

    static PESPacket *GetNextPacket(ESPacket::start_code scode, unsigned char stream_id, unsigned short packet_length,
                                    unsigned char *start_pos) {
        switch (scode) {
            case ESPacket::start_code::picture:
                return GetPESPicture(stream_id, packet_length, start_pos);
            case ESPacket::start_code::slice:
                return GetPESSlice(stream_id, packet_length, start_pos);
            case ESPacket::start_code::sequence_header:
                return GetPESSequenceHeader(stream_id, packet_length, start_pos);
            case ESPacket::start_code::extension:
                return GetPESExtension(stream_id, packet_length, start_pos);
            case ESPacket::start_code::group:
                return GetPESGroup(stream_id, packet_length, start_pos);
            case ESPacket::start_code::video_stream:
                return GetPESVideoStream(stream_id, packet_length, start_pos);
            default:
                throw PacketException("ESParser::GetNextPacket:: Invalid Packet type");
        }
    }

