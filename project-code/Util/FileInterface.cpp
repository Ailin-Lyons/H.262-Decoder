//
// Created by bhave on 12/23/2019.
//

#include "FileInterface.h"

    // Linker needs to know where to allocate memory for the static instance
    FileInterface* FileInterface::instance = nullptr;

    /**
     * Setter to initialize the singleton instance.
     * @param relative_path: relative path to load the file from with respect to FileInterface.cpp
     * @throws FileException: if file cannot be opened or the file has invalid size
     */
    void FileInterface::setInstance(char *relativePath) {
        if (relativePath) {
            rf = new std::ifstream(relativePath, std::ios::in | std::ios::binary);
            file_size = getFileSize(relativePath);
            if (!(*rf)) {
                throw FileException("FileInterface::setInstance: Cannot open file!");
            }
            if (file_size == -1 || file_size % 188 != 0) {
                throw FileException("FileInterface::setInstance: Invalid file!");
            }
            num_packets = file_size / 188;

        }
    }

    /**
     * Check if more packets are available. Closes the file if no more packets are available
     * @return true iff there are additional packets in file
     */
    bool FileInterface::HasNextPacket() {
        if (index >= num_packets) {
            if (rf->is_open()) {
                rf->close();
            }
        }
        return index < num_packets;
    }


    /**
     * Reads the data of the next packet into the file_buffer
     * @throws PacketException: if HasNextPacket returns false
     *         FileException: if rf->good() returns false
     */
    void FileInterface::getNextPacketData(char *file_buffer) {
        if (!HasNextPacket()) {
            throw PacketException("FileInterface::getNextPacketData: HasNextPacket returned false");
        }
        if (rf->good()) {
            rf->read(file_buffer, 188);
            index++;
        } else {
            throw FileException("FileInterface::getNextPacketData: rf->good() check failed");
        }
    }


