#include "../Transport Packet Structure/TransportPacket.h"
#include<iostream>
#include<fstream>
#include <sys/stat.h>
#include "AFParser.cpp"

using namespace std;

//
// Created by elnsa on 2019-11-19.
//
class TSParser {
    ifstream *rf;
    int file_size;
    int num_packets;
    char *file_buffer;
    int index = 0;

public:
    /**
     * Constructor
     */
    TSParser(char *relative_path) {
        rf = new ifstream(relative_path, ios::in | ios::binary);
        file_size = getFileSize(relative_path);
        if (!(*rf)) {
            cout << "TSParser::Cannot open file!" << endl; // TODO throw exception
            return;
        }
        if (!isValidFile(relative_path)) {
            cout << "TSParser::Invalid File!" << endl; // TODO throw exception
            return;
        }
        num_packets = file_size / 188;
        file_buffer = new char[188];
    }

    /**
     * Must be called before calling getNextPacket to avoid errors
     * @return true iff current there are additional packets in file
     */
    bool HasNextPacket() {
        return index < num_packets - 1;
    }

    /**
     * HasNextPacket must be called and return true before calling this function
     * Returns the next TS Stream packet from the file as a TransportPacket object
     * @return a TransportPacket object || a null pointer if there was an error loading packet
     */
    TransportPacket *GetNextPacket() {
        index++;
        rf->read(file_buffer, 188);
        if (!rf->good()) {
            cout << "TSParser:: Error occurred at reading time!" << endl; // TODO throw exception
            return nullptr;
        }
        TransportPacket *out = (TransportPacket *) malloc(sizeof(TransportPacket));
        out[0] = buildTransportPacket(file_buffer);
        return out;
    }

    /**
     * // TODO
     * rf.close(); in a destructor
     */


private:
    /**
     * A helper function that determines the length of a file in bytes
     * @param relative_path of the file
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
     * @param relative_path path of the input file
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
     * helper function that creates a TransportPacket object given a TS packet in binary data
     * @param packet: TS Packet in binary form
     * @return a TransPortPacket Object containing all fields and data from binary packet
     */
    TransportPacket buildTransportPacket(char *packet) {
        TransportPacket::transport_header_fields thf_out;
        thf_out.sync_byte = packet[0];
        thf_out.transport_error_indicator = (packet[1] >> 7) & 0x1;
        thf_out.payload_unit_start_indicator = packet[1] >> 6 & 0x1;
        thf_out.transport_priority = packet[1] >> 5 & 0x1;
        thf_out.pid = TransportPacket::getPID(packet[2] + ((packet[1] & 0x1F) << 8));
        thf_out.transport_scrambling_control = TransportPacket::getTSC(packet[3] >> 6 & 0x3);
        thf_out.adaptation_field_control = TransportPacket::getAFC(packet[3] >> 4 & 0x3);
        thf_out.continuity_counter = packet[3] & 0xF;
        char *index = (char *) &(packet[4]);
        AdaptationField *adaptationField;
        if (thf_out.adaptation_field_control == TransportPacket::AFC::AFieldOnly ||
            thf_out.adaptation_field_control == TransportPacket::AFC::AFieldPayload) {
            index = AFParser::generateAdaptationField(&packet[4], adaptationField);
        }
        char *data = (char *) malloc(sizeof(char) * (188 - (index - packet)));
        if (thf_out.adaptation_field_control == TransportPacket::AFC::AFieldPayload ||
            thf_out.adaptation_field_control == TransportPacket::AFC::PayloadOnly) {
            for (int i = 0; i < (188 - (index - packet)); i++) {
                data[i] = index[i];
            }
        }
        return TransportPacket(thf_out, adaptationField, data);
    }
};

