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
 * ESParser is a singleton that parses the Elementary stream, drops unhandled packets and parses elementary stream packets into ESPacket objects
 */
class ESParser { //TODO test this entire class
public:
    TransportPacket *currTP; //The TransportPacket currently being parsed
    TransportPacket *nextTP = 0;
    unsigned char *currPos; //The address of currTP that will be parsed next
    unsigned short currOffset; //The bit offset of the current index
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
     * Gives the next TransportPacket if requested by a parser and updates the corresponding
     * private fields
     * @return TransportPacket* - next Transport Packet in sequence;
     */
    TransportPacket *giveNextPacket();

    /**
     * Returns the next numBits bits from the Elementary stream
     * @param numBits up to 64, the number of bits to be read
     * @return
     */
    unsigned long long peekNBits(unsigned int numBits);

    /**
     * Returns the next numBits bits from the Elementary stream
     * Also increments the index of the Elementary stream
     * @param numBits up to 64, the number of bits to be read
     * @return
     */
    unsigned long long popNBits(unsigned int numBits);


private:
    /**
     * A private constructor for the singleton
     */
    ESParser();

    /**
     * Searches the TS for the next ESPacket that is handled.
     * Parses and returns that packet
     */
    ESPacket *getNextVideoPacket(ESPacket::start_code scode, unsigned char stream_id);

    /**
     * See H.262 5.2.3
     * Searches the TS for the next startCode
     * and updates currPos to that index
     */
    void next_start_code();

    bool bytealigned();

    unsigned int numBitsRemaining();

    unsigned long long peekNextPacket(unsigned int numBits);

    void incrementOffset(unsigned int numBits);

    /**
     * finds the beginning of the next Packet that is handled by the decoder
     * and updates currPos to that index
     */
    void findNextValidPacket();

    /**
    * Request the next TSPacket from TSParser and initiates currPos and endPos to wrap around this TSPackets data
    */
    void loadNextTSPacket();
};

#endif //PROJECT_CODE_ESPARSER_H