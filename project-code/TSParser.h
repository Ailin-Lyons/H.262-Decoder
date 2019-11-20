//
// Created by elnsa on 2019-11-19.
//

#include "TransportPacket.h"

#ifndef PROJECT_CODE_TSPARSER_H
#define PROJECT_CODE_TSPARSER_H

#endif //PROJECT_CODE_TSPARSER_H

static class TSParser {
private:
    static int getFileSize(char *relativePath);

    static bool isValidFile(char *relativePath);

public:
    static TransportPacket *ParseFileIntoPackets(char *fileName, char *path);
};