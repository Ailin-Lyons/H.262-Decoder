//
// Created by elnsa on 2020-01-03.
//

#ifndef PROJECT_CODE_ESPARSER_H
#define PROJECT_CODE_ESPARSER_H

#include "../ESPackets/ESPacket.h"
#include "../TSPayloadSections/ProgramAssociationSection.h"
#include "../TSPayloadSections/ProgramMapSection.h"
#include "../TransportPacketStructure/TransportPacket.h"

/**
 * ESParser is a singleton that parses the Elementary stream, drops unhandled packets and parses elementary stream packets into ESPacket objects
 */
class ESParser { //TODO test the H262 portion of this class
public:
    TransportPacket *currTP; //The TransportPacket currently being parsed
    TransportPacket *nextTP = 0; //The next Transport packet to be used. if this is 0 request a new packet instead
    ProgramAssociationSection *programAssociationSection;
    ProgramMapSection *programMapSection;
    unsigned char *currPos; //The address of currTP that will be parsed next
    unsigned short currOffset; //The bit offset of the current index
    unsigned char *endPos; //if currPos >= endPos then a new packet must be fetched
    unsigned int program_pid; //the PID of the program being decoded

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

    /**
    * Searches for a Program Assosciation Section and picks the first program
    * Then searches for the corresponding program map section and uses it to initialize ESParser fields
    */
    void initiateStream();

    /**
    * finds the beginning of the next Packet that is handled by the decoder
    * and updates currPos to that index
    */
    unsigned char nextESPacketID();


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

    /**
     * Checks if current index is byte aligned
     * @return true iff currOffset = 0
     */
    bool bytealigned();

    /**
     * Counts how many bits remain in current Transport Packet
     * @return the number of Bits remaining in the current packet
     */
    unsigned int numBitsRemaining();

    /**
     * Read bits from the next packet without shifting index from current packet
     * @param numBits
     * @return
     */
    unsigned long long peekNextPacket(unsigned int numBits);

    /**
     * Increments the currIndex and currOffset to point numBits further
     * @param numBits the number of bits to shift the index by
     */
    void incrementOffset(unsigned int numBits);


    /**
    * Request the next TSPacket from TSParser and initiates currPos and endPos to wrap around this TSPackets data
    */
    void loadNextTSPacket();

    /**
     * Will discard TSPackets until it finds one with PID == program_pid and returns it
     * @return
     */
    TransportPacket *findNextTSPacket();

    ESPacket *getExtensionPacket();
};

#endif //PROJECT_CODE_ESPARSER_H