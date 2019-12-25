//
// Created by bhave on 12/23/2019.
//

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "FileException.cpp"
#include "../PacketParsers/PacketException.cpp"
#include "InitializationException.cpp"

class FileInterface {
private:
    std::ifstream *rf;
    int file_size;
    int num_packets;
    int index = 0;
    static FileInterface *instance;

    FileInterface() = default;


    /**
    * A helper function that determines the length of a file in bytes
    * @param relative_path: relative path to load the file from with respect to TSParser.cpp
    * @return length of file in bytes || -1 if error
    */
    static int getFileSize(char *relative_path) {
        struct stat results;

        if (stat(relative_path, &results) == 0)
            return results.st_size;
        else return -1;
    }


public:

    /**
     * Function to return a pointer to the singleton instance
     * @return FileInterface* instance
     */
    static FileInterface *getInstance() {
        if (!instance) {
            instance = new FileInterface();
        }
        return instance;
    }


    /**
     * Setter to initialize the singleton instance.
     * @param relative_path: relative path to load the file from with respect to FileInterface.cpp
     * @throws FileException: if file cannot be opened or the file has invalid size
     */
    void setInstance(char *relativePath) {
        if (relativePath) {
//            if (!instance) {
//                getInstance();
//            }
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
    bool HasNextPacket() {
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
    void getNextPacketData(char *file_buffer) {
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
};

