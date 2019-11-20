//
// Created by elnsa on 2019-11-19.
//

#include "TransportPacket.h"

#ifndef PROJECT_CODE_TSPARSER_H
#define PROJECT_CODE_TSPARSER_H

#endif //PROJECT_CODE_TSPARSER_H

class TSParser {
private:
    static int getFileSize(char *relativePath);

    static bool isValidFile(char *relativePath);

    static TransportPacket buildTransportPacket(char* packet);

public:
    /**
     * Parses a .ts file and returns a pointer to an array of pointers to TransportPackets
     * Will throw an exception if there is an issue loading
     * @param relativePath the relativePath of the .ts file to be read
     * @return a pointer to an array of pointers to TransportPackets. the caller is responsible for freeing
     */
    static TransportPacket *ParseFileIntoPackets(char *relativePath);
};