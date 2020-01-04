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
    ESPacket* GetNextPacket();

private:
    PESPacket *GetNextVideoPacket(ESPacket::start_code scode, unsigned char stream_id);

};
#endif //PROJECT_CODE_ESPARSER_H