//
// Created by elnsa on 2020-01-15.
//

#ifndef PROJECT_CODE_VIDEODECODER_H
#define PROJECT_CODE_VIDEODECODER_H

#include "Util/FileInterface.h"
#include "PacketParsers/ESParser.h"

class VideoDecoder {
public:
    static VideoDecoder *instance;

    unsigned short getHorizontalSize() const;

    unsigned short getVerticalSize() const;
    // H.262 6.3.3


    /**
   * Function to return a pointer to the singleton instance
   * @return VideoDecoder* instance
   */
    static VideoDecoder *getInstance() {
        if (!instance) {
            instance = new VideoDecoder();
        }
        return instance;
    }

    void decodeToFile(char *source, char *destination);

private:
    /**
     * Fields
     */
    unsigned short horizontal_size; // H.262 6.3.3
    unsigned short vertical_size;

    /**
     * A private constructor for the singleton
     */
    VideoDecoder();

    bool loadFile(char *relative_path);

    void loadVideoSequence();

    ESPacket *getNextVideoPacket();
};


#endif //PROJECT_CODE_VIDEODECODER_H
