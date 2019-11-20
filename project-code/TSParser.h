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
     * Parses a .ts file and returns a set of TransportPacket objects representing each packet in the file
     * Will throw an exception if there is an issue loading
     * @param relativePath the relativePath of the .ts file to be read
     * @return an array of TransportPackets. the caller is responsible for freeing
     */
    static TransportPacket *ParseFileIntoPackets(char *relativePath);
};