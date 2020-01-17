//
// Created by elnsa on 2020-01-16.
//

#ifndef PROJECT_CODE_VIDEOINFORMATION_H
#define PROJECT_CODE_VIDEOINFORMATION_H

class VideoInformation {
private:
    static VideoInformation *instance;
    /**
     * Fields
     */
    unsigned short horizontal_size; // H.262 6.3.3
    unsigned short vertical_size; // H.262 6.3.3

    /**
     * A private constructor for the singleton
     */
    VideoInformation() = default;

public:

    static VideoInformation *getInstance() {
        if (!instance) {
            instance = new VideoInformation();
        }
        return instance;
    }

    /**
     * Public Functions
     */

    unsigned short getHorizontalSize() const;

    unsigned short getVerticalSize() const;

    void setHorizontalSize(unsigned short horizontalSize);

    void setVerticalSize(unsigned short verticalSize);
};

#endif //PROJECT_CODE_VIDEOINFORMATION_H
