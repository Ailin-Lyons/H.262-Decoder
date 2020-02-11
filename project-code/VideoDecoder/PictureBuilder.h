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
public:
    static cimg_library::CImg<int> *makePngFromHPicture(HPicture *hPicture);

private:
    static Macroblock *getNthMacroblock(HPicture *pPicture, size_t n);

    static void addMacroblockToCimg(cimg_library::CImg<int> *image, Macroblock *macroblock, size_t macroblockNumber);

    static void addYBlockToCimg(cimg_library::CImg<int> *image, Block *yBlock, size_t topleft);

    static void addCbBlockToCimg(cimg_library::CImg<int> *image, Block *bBlock, size_t topleft);

    static void addCrBlockToCimg(cimg_library::CImg<int> *image, Block *rBlock, size_t topleft);

    static size_t getTopLeftIndex(size_t number);
};


#endif //PROJECT_CODE_PICTUREBUILDER_H
