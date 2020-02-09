//
// Created by elnsa on 2020-02-08.
//

#ifndef PROJECT_CODE_PICTUREBUILDER_H
#define PROJECT_CODE_PICTUREBUILDER_H

#define cimg_use_png

#include "../CImg283/CImg.h"
#include "../PictureDecoder/HPicture.h"
#include "VideoException.cpp"
#include "VideoInformation.h"

class PictureBuilder {

private:
    static void macroBlockHandler(cimg_library::CImg<int>* img, Macroblock*,size_t x, size_t y);
    static void updatePositions(size_t *x, size_t* y);

public:
    static cimg_library::CImg<int>* makePngFromHPicture(HPicture* hPicture);
};


#endif //PROJECT_CODE_PICTUREBUILDER_H
