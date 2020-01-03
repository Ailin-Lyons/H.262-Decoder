//
// Created by elnsa on 2019-12-23.
//
#include "../ESPackets/PESPacket.h"
#include "../Util/BitManipulator.cpp"
#include "../TransportPacketStructure/TransportPacket.h"
#include "PacketException.cpp"


#define MAXPACKETS 46

class PESParser {
public:
    /**
    * Struct that contains all return fields of parsePESPackets
    */
    struct pes_packet_array {
        unsigned char num_packets; // size of array
        PESPacket **packet_array; // array of PESPackets of size num_packets
    };

    /**
     * Parses the data field from tp into individual PES Packets.
     * Ignores any packets not handled by this decoder.
     * @param tp a pointer to a valid TransportPacket
     * @return a struct of type pes_packet_array that contains num_packets PESPacket* in packet_array
     * Caller is responsible for freeing each PESPacket as well as packet_array
     */
    static pes_packet_array ParseTransportPacketData(TransportPacket *tp) {
        pes_packet_array out = {};
        unsigned char *currPosition = tp->data;
        unsigned char *endPosition = tp->data + tp->data_length;
        PESPacket *tempArray[MAXPACKETS];
        unsigned int numPackets = 0;
        while (currPosition + 5 < endPosition) {
            unsigned int packet_start_code_prefix = BitManipulator::ReadNBits(currPosition, 24);
            currPosition += 3;
            if (packet_start_code_prefix != 0x000001) {
                throw PacketException("PESParser::Invalid packet_start_code_prefix!");
                // We may want to deliberatly clean out stuffing bytes in future
            }
            unsigned char stream_id = BitManipulator::ReadNBits(currPosition, 8);
            currPosition++;
            ESPacket::start_code packet_type = ESPacket::GetStartCode(stream_id);
            unsigned short PES_packet_length = BitManipulator::ReadNBits(currPosition, 16);
            currPosition += 2;
            if (currPosition + PES_packet_length <= endPosition && ESPacket::IsHandled(packet_type)) {
                tempArray[numPackets] = GetNextPacket(packet_type, stream_id, PES_packet_length, currPosition);
                numPackets++;
                if (numPackets > MAXPACKETS) {
                    throw PacketException("PESParser::MAXPACKETS exceeded!");
                }
            }
        }
        out.num_packets = numPackets;
        out.packet_array = (PESPacket **) malloc(sizeof(PESPacket *) * numPackets);
        for (int i = 0; i < numPackets; i++) {
            out.packet_array[i] = tempArray[i];
        }
        return out;
    }

private:

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
                throw PacketException("PESParser::GetNextPacket:: Invalid Packet type");
        }
    }

};

