//
// Created by elnsa on 2020-01-15.
//

#ifndef PROJECT_CODE_VIDEODECODER_H
#define PROJECT_CODE_VIDEODECODER_H

#include <ESPacket.h>

class VideoDecoder {
private:
    static VideoDecoder *instance;

    /**
     * A private constructor for the singleton
     */
    VideoDecoder();

    bool loadFile(char *relative_path);

    void loadVideoSequence();

    ESPacket *getNextVideoPacket();

public:
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

};


#endif //PROJECT_CODE_VIDEODECODER_H
