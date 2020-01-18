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

    static bool loadFile(char *relative_path);

    void loadVideoSequence();

    static ESPacket *getNextVideoPacket();

    static bool isNextVideoPacket(ESPacket::start_code startCode);

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

    void loadExtensionUserData(unsigned char i);

    void loadGroupHeaderAndExtension();

    void loadPictureHeader();

    void loadPictureCodingExtension();

    void loadPictureData();

    static void handleVideoStream(ESPacket *pPacket);

    void makePicture();
};


#endif //PROJECT_CODE_VIDEODECODER_H
