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
    /**
     * Constructor
     */
public:
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

    bool HasNextPacket() {
        return index < num_packets - 1;
    }

    /**
     *
     * @return
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
    int getFileSize(char *relative_path) {
        struct stat results;

        if (stat(relative_path, &results) == 0)
            return results.st_size;
        else return -1;
    }

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

    TransportPacket buildTransportPacket(char *packet) {
        unsigned char sync_byte = packet[0];
        unsigned char transport_error_indicator = (packet[1] >> 7) & 0x1;
        unsigned char payload_unit_start_indicator = packet[1] >> 6 & 0x1;
        unsigned char transport_priority = packet[1] >> 5 & 0x1;
        unsigned short pid = packet[2] + ((packet[1] & 0x1F) << 8);
        unsigned char transport_scrambling_control = packet[3] >> 6 & 0x3;
        unsigned char adaptation_field_control = packet[3] >> 4 & 0x3;
        unsigned char continuity_counter = packet[3] & 0xF;
        char *index = (char *) &(packet[4]);
        AdaptationField *adaptationField;
        if (adaptation_field_control == 0x2 || adaptation_field_control == 0x3) {
            index = AFParser::generateAdaptationField(&packet[4], adaptationField);
        }
        char *data = (char *) malloc(sizeof(char) * (188 - (index - packet)));
        if (adaptation_field_control == 0x1 || adaptation_field_control == 0x3) {
            for (int i = 0; i < (188 - (index - packet)); i++) {
                data[i] = index[i];
            }
        }
        return TransportPacket(sync_byte, transport_error_indicator, payload_unit_start_indicator,
                               transport_priority, pid, transport_scrambling_control, adaptation_field_control,
                               continuity_counter, adaptationField, data);
    }
};

