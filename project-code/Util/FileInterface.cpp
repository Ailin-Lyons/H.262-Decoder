//
// Created by bhave on 12/23/2019.
//

#include "FileInterface.h"
#include "FileException.cpp"
#include "../PacketParsers/PacketException.cpp"

// Linker needs to know where to allocate memory for the static instance
FileInterface *FileInterface::instance = nullptr;

/**
 * Setter to initialize the singleton instance.
 * @param relativePath: relative path to load the file from with respect to FileInterface.cpp
 * @throws FileException: if file cannot be opened or the file has invalid size
 */
void FileInterface::setInstance(char *relativePath) {
    if (relativePath) {
        if (rf && rf->is_open()) {
            rf->close();
            rf = nullptr;
        }
        rf = new std::ifstream(relativePath, std::ios::in | std::ios::binary);
        file_size = getFileSize(relativePath);
        if (!(*rf)) {
            throw FileException("FileInterface::setInstance: Cannot open file!\n");
        }
        if (file_size == -1 || file_size % 188 != 0) {
            throw FileException("FileInterface::setInstance: Invalid file!\n");
        }
        index = 0;
        num_packets = file_size / 188;
    }
}

/**
 * Check if more packets are available. Closes the file if no more packets are available
 * @return true iff there are additional packets in file
 */
bool FileInterface::hasNextPacket() {
    if (index >= num_packets) {
        if (rf->is_open()) {
            rf->close();
        }
    }
    return index < num_packets;
}


/**
 * Reads the data of the next packet into the file_buffer
 * @throws PacketException: if hasNextPacket returns false
 *         FileException: if rf->good() returns false
 */
void FileInterface::getNextPacketData(char *file_buffer) {
    if (!hasNextPacket()) {
        throw PacketException("FileInterface::getNextPacketData: hasNextPacket returned false\n");
    }
    if (rf->good()) {
        rf->read(file_buffer, 188);
        index++;
    } else {
        throw FileException("FileInterface::getNextPacketData: rf->good() check failed\n");
    }
}

FileInterface::~FileInterface() {
    if (instance && instance->rf->is_open()) {
        instance->rf->close();
        instance->rf = nullptr;
    }
    delete instance;
    instance = nullptr;
}
