//
// Created by elnsa on 2020-01-03.
//

#ifndef PROJECT_CODE_ESPARSER_H
#define PROJECT_CODE_ESPARSER_H

#include "../ESPackets/PESPacket.h"
#include "TSParser.cpp"
#include "../Util/BitManipulator.cpp"
#include "../TransportPacketStructure/TransportPacket.h"
#include "PacketException.cpp"

/**
 * ESParser parses the Elementary stream, drops unhandled packets and parses elementary stream packets into ESPacket objects
 */
class ESParser { //TODO test this entire class
public:
    TransportPacket *currTP; //The TransportPacket currently being parsed
    unsigned char *currPos; //The address of currTP that will be parsed next
    unsigned char *endPos; //if currPos >= endPos then a new packet must be fetched
    bool isVideoStream; //if Elementary stream is a video_stream this boolean is true
    char currVideoStreamID; //if isVideoStream then this is the id of the stream

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
    * Returns the next elementary stream packet if it
    * Ignores any packets not handled by this decoder.
    * @return one of many possible packets that implements the ESPacket interface.
    */
    ESPacket *getNextPacket();

    /**
     * Reads and returns the next numBits from the TransportPackets
     * @param numBits - number of bits to be read
     * @return unsigned long long - lowest order 64 bits as requested
     */
    static unsigned long long readNBits(unsigned int numBits);

private:
    /**
     * Searches the TS for the next ESPacket that is handled.
     * Parses and returns that packet
     */
    ESPacket *getNextVideoPacket(ESPacket::start_code scode, unsigned char stream_id);

    /**
     * Searches the TS for the next startCode
     * and updates currPos to that index
     */
    void findNextStartCode();

    /**
     * finds the beginning of the next Packet that is handled by the decoder
     * and updates currPos to that index
     */
    void findNextValidPacket();

    /**
    * Request the next TSPacket from TSParser and initiates currPos and endPos to wrap around this TSPackets data
    */
    void loadNextTSPacket();

    /**
     *  Constructor
     */
    ESParser();
};

#endif //PROJECT_CODE_ESPARSER_H