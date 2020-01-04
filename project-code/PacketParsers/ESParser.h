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

    static ESParser *instance;

    /**
    * Function to return a pointer to the singleton instance
    * @return ESParser* instance
    */
    static ESParser *getInstance() {
        if (!instance) {
            instance = new ESParser();
        }
        return instance;
    }


    /**
     * Returns the next elementary stream packet if it exists
     * Ignores any packets not handled by this decoder.
     * @param tp a pointer to a valid TransportPacket
     * @return a struct of type pes_packet_array that contains num_packets PESPacket* in packet_array
     * Caller is responsible for freeing each PESPacket as well as packet_array
     */
    ESPacket* GetNextPacket();
    ESPacket *GetNextVideoPacket(ESPacket::start_code scode, unsigned char stream_id);

    /**
     * Gives the next TransportPacket if requested by a parser and updates the corresponding
     * private fields
     * @return TransportPacket* - next Transport Packet in sequence;
     */
    TransportPacket* giveNextPacket();

    ESParser();
};
#endif //PROJECT_CODE_ESPARSER_H