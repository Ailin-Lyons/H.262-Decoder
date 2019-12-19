#include "../TransportPacketStructure/TransportPacket.h"
#include "../TransportPacketStructure/AdaptationField.h"
#include<iostream>
#include<fstream>
#include <sys/stat.h>
#include "AFParser.cpp"

//using namespace std;

//
// Created by elnsa on 2019-11-19.
//
class TSParser {
    std::ifstream *rf;
    int file_size;
    int num_packets;
    char *file_buffer;
    int index = 0;

public:

    /**
     * Explicit Constructor
     */
    explicit TSParser(char *relative_path) {
        rf = new std::ifstream(relative_path, std::ios::in | std::ios::binary);
        file_size = getFileSize(relative_path);
        // TODO - change to using the builtin error checking to throw the exceptions
        if (!(*rf)) {
            std::cout << "TSParser::Cannot open file!" << std::endl; // TODO throw exception
            return;
        }
        if (!isValidFile(relative_path)) {
            std::cout << "TSParser::Invalid File!" << std::endl; // TODO throw exception
            return;
        }
        num_packets = file_size / 188;
        file_buffer = new char[188];
    }

    /**
     * Must be called before calling getNextPacket to avoid errors
     * @return true iff there are additional packets in file
     */
    bool HasNextPacket() {
        return index < num_packets;
    }


    // DESIGN - maybe just call HasNextPacket in GetNextPacket as well and throw an exception

    /**
     * HasNextPacket must be called and return true before calling this function
     * Returns the next TS Stream packet from the file as a TransportPacket object
     * @return a TransportPacket object || a null pointer if there was an error loading packet
     */
    TransportPacket *GetNextPacket() {
        rf->read(file_buffer, 188);
        if (!rf->good()) {
            std::cout << "TSParser:: Error occurred at reading time!" << std::endl; // TODO throw exception
            return nullptr;
        }
        TransportPacket *out = (TransportPacket *) malloc(sizeof(TransportPacket));
        out[0] = buildTransportPacket((unsigned char *) file_buffer);
        index++;
        return out;
    }

    /**
     * // TODO
     * rf.close(); in a destructor
     */


private:
    /**
     * A helper function that determines the length of a file in bytes
     * @param relative_path - path of the file
     * @return length of file in bytes || -1 if error
     */
    int getFileSize(char *relative_path) {
        struct stat results;

        if (stat(relative_path, &results) == 0)
            return results.st_size;
        else return -1;
    }

    /**
     * A helper function that verifies that the input file is valid
     * @param relative_path - path of the input file
     * @return true iff file exists and is multiple of 188 bytes
     */
    bool isValidFile(char *relative_path) {
        int file_size = TSParser::getFileSize(relative_path);
        if (file_size == -1) {
            return false; // Error getting file size
        } else if (file_size % 188 != 0) {
            return false; // File is not a multiple of 188 bytes
        } else {
            return true;
        }
    }

    /**
     * Helper function that creates a TransportPacket object given a TS packet in binary data
     * @param packet: TS Packet in binary form
     * @return a TransportPacket Object containing all fields and data from binary packet
     */
    TransportPacket buildTransportPacket(unsigned char *packet) {
        size_t index = 0;
        TransportPacket::transport_header_fields thf_out;
        thf_out.sync_byte = packet[index];
        index++;
        thf_out.transport_error_indicator = BitManipulator::ReadNBits(&packet[index], 1);
        thf_out.payload_unit_start_indicator = BitManipulator::ReadNBitsOffset(&packet[index], 1, 1);
        thf_out.transport_priority = BitManipulator::ReadNBitsOffset(&packet[index], 2, 1);
        thf_out.pid = TransportPacket::getPID(BitManipulator::ReadNBitsOffset(&packet[index], 3, 13));
        index += 2;
        thf_out.transport_scrambling_control = TransportPacket::getTSC(BitManipulator::ReadNBits(&packet[index], 2));
        thf_out.adaptation_field_control = TransportPacket::getAFC(
                BitManipulator::ReadNBitsOffset(&packet[index], 2, 2));
        thf_out.continuity_counter = BitManipulator::ReadNBitsOffset(&packet[index], 4, 4);
        index++;
        AdaptationField adaptationField;
        if (thf_out.adaptation_field_control == TransportPacket::AFC::AFieldOnly ||
            thf_out.adaptation_field_control == TransportPacket::AFC::AFieldPayload) {
            adaptationField = AFParser::generateAdaptationField(&packet[index]);
            index += adaptationField.adaptation_field_length + 1; // see H.222 2.4.3.5
        }
        char *data = (char *) malloc(sizeof(char) * (188 - index));
        if (thf_out.adaptation_field_control == TransportPacket::AFC::AFieldPayload ||
            thf_out.adaptation_field_control == TransportPacket::AFC::PayloadOnly) {
            for (int i = 0; index < 188; i++) {
                data[i] = packet[index];
                index++;
            }
        }
        return TransportPacket(thf_out, adaptationField, data);
    }
};
