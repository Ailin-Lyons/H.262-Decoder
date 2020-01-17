//
// Created by elnsa on 2020-01-16.
//
#include "VideoInformation.h"

VideoInformation *VideoInformation::instance = nullptr;

unsigned short VideoInformation::getHorizontalSize() const {
    return horizontal_size;
}

unsigned short VideoInformation::getVerticalSize() const {
    return vertical_size;
}

void VideoInformation::setHorizontalSize(unsigned short horizontalSize) {
    horizontal_size = horizontalSize;
}

void VideoInformation::setVerticalSize(unsigned short verticalSize) {
    vertical_size = verticalSize;
}
