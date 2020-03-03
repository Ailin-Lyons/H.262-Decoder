//
// Created by bhave on 12/30/2019.
//

#ifndef PROJECT_CODE_FILEINTERFACE_H
#define PROJECT_CODE_FILEINTERFACE_H


#include <iostream>
#include <fstream>
#include <sys/stat.h>

/**
 * Singleton class that deals with I/O operations
 */

class FileInterface {
private:
    std::ifstream *rf{};
    int file_size{};
    int num_packets{};
    int index = 0;
    static FileInterface *instance;

    FileInterface() = default;

    ~FileInterface();

    /**
    * A helper function that determines the length of a file in bytes
    * @param relative_path: relative path to load the file from with respect to FileInterface.h
    * @return length of file in bytes || -1 if error
    */
    static int getFileSize(char *relative_path) {
        struct stat results = {};
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
     * Setter to initialize the singleton instance. Closes the previous instance if already initialized
     * @param relativePath: relative path to load the file from with respect to FileInterface.cpp
     * @throws FileException: if file cannot be opened or the file has invalid size
     */
    void setInstance(char *relativePath);

    /**
     * Check if more packets are available. Closes the file if no more packets are available
     * @return true iff there are additional packets in file
     */
    bool hasNextPacket();


    /**
     * Reads the data of the next packet into the file_buffer
     * @throws PacketException: if hasNextPacket returns false
     *         FileException: if rf->good() returns false
     */
    void getNextPacketData(char *file_buffer);


};

#endif //PROJECT_CODE_FILEINTERFACE_H
