#include "TransportPacket.h"
#include<iostream>
#include<fstream>
#include <sys/stat.h>

using namespace std;

class TSParser {
private:
    static int getFileSize(char *relativePath) {
        struct stat results;

        if (stat(relativePath, &results) == 0)
            return results.st_size;
        else return -1;
    }

    static bool isValidFile(char *relativePath) {
        int filesize = TSParser::getFileSize(relativePath);
        if (filesize == -1) {
            return false; // Error getting file size
        } else if (filesize % 188 != 0) {
            return false; // File is not a multiple of 188 bytes
        } else {
            return true;
        }
    }

    static TransportPacket buildTransportPacket(const char *packet) {
        unsigned char sync_byte = packet[0];
        unsigned char transport_error_indicator = (packet[1] >> 7) & 0x1;
        unsigned char payload_unit_start_indicator = packet[1] >> 6 & 0x1;
        unsigned char transport_priority = packet[1] >> 5 & 0x1;
        unsigned short pid = packet[2] + ((packet[1] & 0x1F) << 8);
        unsigned char transport_scrambling_control = packet[3] >> 6 & 0x3;
        unsigned char adaptation_field_control = packet[3] >> 4 & 0x3;
        unsigned char continuity_counter = packet[3] & 0xF;
        printf("Stuff%x|%x|%x|%x|%x|%x|%x|%x\n", sync_byte, transport_error_indicator, payload_unit_start_indicator,
              transport_priority, pid, transport_scrambling_control, continuity_counter);
        // TODO initialize these values
        return TransportPacket(sync_byte, transport_error_indicator, payload_unit_start_indicator,
                               transport_priority, pid, transport_scrambling_control, adaptation_field_control,
                               continuity_counter);
    }

public:
    static TransportPacket *ParseFileIntoPackets(char *relativePath) {
        ifstream rf(relativePath, ios::in | ios::binary);
        int fileSize = getFileSize(relativePath);
        if (!rf) {
            cout << "Cannot open file!" << endl; // TODO turn this into an exception and throw
            return nullptr;
        }
        if (TSParser::isValidFile(relativePath)) {
            int numPackets = fileSize / 188;
            char *fileBuffer = new char[fileSize];
            rf.read(fileBuffer, fileSize);
            rf.close();
            if (!rf.good()) {
                cout << "Error occurred at reading time!" << endl; // TODO turn this into an exception and throw
                return nullptr;
            }
            TransportPacket *out = (TransportPacket *) malloc(sizeof(TransportPacket) * numPackets);
            for (int i = 0; i < numPackets; i++) {
                out[i] = buildTransportPacket(&(fileBuffer[i * 188]));
            }
            return out;
        } else {
            return nullptr; // TODO throw a invalid file exception
        }
    }
};

