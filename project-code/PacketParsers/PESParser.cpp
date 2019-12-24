//
// Created by elnsa on 2019-12-23.
//
#include "../PesPacket/PESPacket.h"
#include "../Util/BitManipulator.cpp"
#include "../TransportPacketStructure/TransportPacket.h"

class PESParser { //TODO this class will have a switch statement and delegate individual packets

public:

    /**
    * Struct that contains all return fields of parsePESPackets
    */
    struct pes_parser_struct {
        unsigned char num_packets; // size of array
        PESPacket *packet_array; // array of PESPackets of size num_packets
    };

    /**
     * //TODO stub
     */
    static pes_parser_struct parseTransportPacket(TransportPacket *tp) {
        pes_parser_struct out; //TODO build this struct and return at end. It should contain all PES packets
        unsigned char *currPosition = tp->data;
        unsigned int numBytesLeft = tp->data_length;
        while (numBytesLeft > 0) {
            if (HasNextPacket(currPosition, numBytesLeft)) {
                currPosition += 3; //Bypass packet_start_code_prefix
                numBytesLeft -= 3;
                unsigned char start_code = BitManipulator::ReadNBits(currPosition, 8);
                if (start_code >= 0x01 && start_code <= 0xAF) {
                    //TODO handle slice()
                } else if (start_code >= 0xC0 && start_code <= 0xDF) {
                    //TODO make stub for handling audio
                } else if (start_code >= 0xE0 && start_code <= 0xEF) {
                    //TODO handle video stream
                } else if (start_code >= 0xFA && start_code <= 0xFE) {
                    //TODO stub for reserved data stream
                } else {
                    switch (start_code) {
                        case 0x00 :
                            //TODO handle picture_start_code
                            break;
                        case 0xB0 :
                        case 0xB1 :
                            //TODO stub for reserved
                            break;
                        case 0xB2 :
                            //TODO handle user_data?
                            break;
                        case 0xB3 :
                            //TODO handle sequence_header_code
                            break;
                        case 0xB4 :
                            //TODO handle sequence_error_code?
                            break;
                        case 0xB5 :
                            //TODO handle extension_start_code
                            break;
                        case 0xB6 :
                            //TODO stub for reserved
                            break;
                        case 0xB7 :
                            //TODO handle sequence_end_code?
                            break;
                        case 0xB8 :
                            //TODO handle group_start_code?
                            break;
                        case 0xBC :
                            //TODO handle program_stream_map?
                            break;
                        case 0xBD :
                            //TODO stub for private_stream_1?
                            break;
                        case 0xBE :
                            //TODO handle padding_stream?
                            break;
                        case 0xBF :
                            //TODO stub for private_stream_2?
                            break;
                        case 0xF0 :
                            //TODO stub for ECM_stream?
                            break;
                        case 0xF1 :
                            //TODO stub for EMM_stream?
                            break;
                        case 0xF2 :
                            //TODO stub for ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Annex B or ISO/IEC 13818-6_DSMCC_stream?
                            break;
                        case 0xF3 :
                            //TODO stub for ISO/IEC_13522_stream?
                            break;
                        case 0xF4 :
                            //TODO stub for ITU-T Rec. H.222.1 type A?
                            break;
                        case 0xF5 :
                            //TODO stub for ITU-T Rec. H.222.1 type B?
                            break;
                        case 0xF6 :
                            //TODO stub for ITU-T Rec. H.222.1 type C?
                            break;
                        case 0xF7 :
                            //TODO stub for ITU-T Rec. H.222.1 type D?
                            break;
                        case 0xF8 :
                            //TODO stub for ITU-T Rec. H.222.1 type E?
                            break;
                        case 0xF9 :
                            //TODO stub for ancillary_stream?
                            break;
                        case 0xFF :
                            //TODO stub for program_stream_directory?
                            break;
                        default :
                            std::cerr << "PESParser::Unexpected start_code in TransportPacket: " << start_code
                                      << std::endl;
                            throw;
                    }
                }
            } else if (BitManipulator::ReadNBits(currPosition, 8) == 0xFF) { // Remove stuffing byte
                currPosition++;
                numBytesLeft--;
            } else {
                std::cerr << "PESParser::Unexpected Data in TransportPacket!" << std::endl;
                throw;
            }
        }
        return out;
    }

private:

/**
 * //TODO might need a function like this?
 */
    static bool HasNextPacket(unsigned char *currPosition, unsigned int numBytesLeft) {
        if (numBytesLeft < 4) {
            return false; //Not enough space for another packet;
        }
        if (numBytesLeft >= 4) { //4 is minimum bytes needed to
            if (BitManipulator::ReadNBits(currPosition, 24) == 0x000001) {
                return true;
            }
            HasNextPacket(currPosition, numBytesLeft);
        }
        return false;
    }

};

