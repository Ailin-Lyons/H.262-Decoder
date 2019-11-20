#include "TransportPacket.h"
#include "TSParser.h"
#include<iostream>
#include<fstream>
#include <sys/stat.h>

using namespace std;

//
// Created by elnsa on 2019-11-19.
//
int TSParser::getFileSize(char *relativePath) {
    struct stat results;

    if (stat("input.bin", &results) == 0)
        return results.st_size;
    else return -1;
}

bool TSParser::isValidFile(char *relativePath) {
    int filesize = TSParser::getFileSize(relativePath);
    if (filesize == -1) {
        return false; // Error getting file size
    } else if (filesize % 188 != 0) {
        return false; // File is not a multiple of 188 bytes
    } else {
        return true;
    }
}

TransportPacket* TSParser::buildTransportPacket(char *packet) {
    unsigned char sync_byte;
    unsigned char transport_error_indicator;
    unsigned char payload_unit_start_indicator;
    unsigned char transport_priority;
    unsigned short pid;
    unsigned char transport_scrambling_control;
    unsigned char adaptation_field_control;
    unsigned char continuity_counter;
    return nullptr; // TODO
}

TransportPacket **TSParser::ParseFileIntoPackets(char *relativePath) {
    relativePath = "test files/testvideo_noaudio.ts"; // TODO remove this line
    ifstream rf(relativePath,
                ios::out | ios::binary);
    int fileSize = getFileSize(relativePath);
    if (!rf) {
        cout << "Cannot open file!" << endl; // TODO turn this into an exception and throw
        return nullptr;
    }
    if (TSParser::isValidFile(relativePath)) {
        int numPackets = fileSize % 188;
        char *fileBuffer = new char[fileSize];
        rf.read((char *) &fileBuffer, fileSize);
        rf.close();
        if (!rf.good()) {
            cout << "Error occurred at reading time!" << endl; // TODO turn this into an exception and throw
            return nullptr;
        }
        TransportPacket **out = (TransportPacket **) malloc(sizeof(TransportPacket*) * numPackets);
        for (int i = 0; i < numPackets; i++) {
            out[i] = buildTransportPacket(&(fileBuffer[i * 188]));
        }
        return out;
    } else {
        return nullptr; // TODO throw a invalid file exception
    }
}


