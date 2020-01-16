//
// Created by elnsa on 2020-01-15.
//

#ifndef PROJECT_CODE_VIDEODECODER_H
#define PROJECT_CODE_VIDEODECODER_H

#include <FileInterface.h>
#include <ESParser.h>

class VideoDecoder {
public:
    static VideoDecoder *instance;

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
    ESPacket::start_code next_start_code;
    /**
     * A private constructor for the singleton
     */
    VideoDecoder();

    bool loadFile(char* relative_path);

    void loadVideoSequence();

    ESPacket* getNextVideoPacket();
};


#endif //PROJECT_CODE_VIDEODECODER_H
