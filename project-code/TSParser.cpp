#include "TransportPacket.h"
#include<iostream>
#include<fstream>
#include <sys/stat.h>

using namespace std;

//
// Created by elnsa on 2019-11-19.
//
static class TSParser {
    static int getFileSize(char *relativePath) {
        struct stat results;

        if (stat("input.bin", &results) == 0)
            return results.st_size;
        else return -1;
    }

    static bool isValidFile(char *relativePath) {
        int filesize = getFileSize(relativePath);
        if (filesize == -1) {
            return false; // Error getting file size
        } else if (filesize % 188 != 0) {
            return false; // File is not a multiple of 188 bytes
        } else {
            return true;
        }
    }

    static TransportPacket *ParseFileIntoPackets(char *relativePath) {
        ifstream rf("test files/testvideo_noaudio.ts",
                    ios::out | ios::binary); // TODO replace filename with relativePath
        if (isValidFile(relativePath)) { // TODO replace filename with relativePath
            int numPackets = getFileSize(relativePath) % 188;
        } else {
            // TODO throw a invalid file exception
        }
        return nullptr; // TODO
    }
};

