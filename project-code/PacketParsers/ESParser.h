//
// Created by elnsa on 2020-01-03.
//

#ifndef PROJECT_CODE_ESPARSER_H
#define PROJECT_CODE_ESPARSER_H
//
// Created by elnsa on 2019-12-23.
//
#include "../ESPackets/PESPacket.h"
#include "TSParser.cpp"
#include "../Util/BitManipulator.cpp"
#include "../TransportPacketStructure/TransportPacket.h"
#include "PacketException.cpp"


#define MAXPACKETS 46

class ESParser {
public:
    TransportPacket* currTP;
    unsigned char* currPos;
    unsigned char* endPos;
    bool isVideoStream;
    char currVideoStreamID;

    ESParser();

    /**
     * Returns the next elementary stream packet if it exists
     * Ignores any packets not handled by this decoder.
     * @param tp a pointer to a valid TransportPacket
     * @return a struct of type pes_packet_array that contains num_packets PESPacket* in packet_array
     * Caller is responsible for freeing each PESPacket as well as packet_array
     */
    ESPacket GetNextPacket();

private:

    static PESPacket *GetPESPicture(unsigned char id, unsigned short length, unsigned char *start_pos);

    static PESPacket *GetPESSlice(unsigned char id, unsigned short length, unsigned char *start_pos);


    static PESPacket *GetPESSequenceHeader(unsigned char id, unsigned short length, unsigned char *start_pos);


    static PESPacket *GetPESExtension(unsigned char id, unsigned short length, unsigned char *start_pos);


    static PESPacket *GetPESGroup(unsigned char id, unsigned short length, unsigned char *start_pos);


    static PESPacket *GetPESVideoStream(unsigned char id, unsigned short length, unsigned char *start_pos);


    static PESPacket *GetNextPacket(ESPacket::start_code scode, unsigned char stream_id, unsigned short packet_length,
                                    unsigned char *start_pos);

};
#endif //PROJECT_CODE_ESPARSER_H
