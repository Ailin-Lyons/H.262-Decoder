//
// Created by elnsa on 2020-02-08.
//

#include "PictureBuilder.h"

cimg_library::CImg<int> *PictureBuilder::makePngFromHPicture(HPicture *picture) {
    if (picture->getState() == HPicture::decoding_state::discrete_cosine_transformed) {
        auto vi = VideoInformation::getInstance();
        auto outImage = new cimg_library::CImg<int>(vi->getHorizontalSize(), vi->getVerticalSize());
        size_t xPos = 0, yPos = 0;
        for (size_t s = 0; s < picture->getNumSlices(); s++) {
            Slice *slice = picture->getSlices()[s];
            for (size_t m = 0; m < slice->getNumMacroblocks(); m++) {
                macroBlockHandler(outImage, &slice->getMacroblocks()[m], xPos, yPos);
                updatePositions(&xPos, &yPos);
            }
        }
        return outImage;
    }
    throw VideoException("PictureBuilder::makePngFromHPicture received HPicture in incorrect decoding_state");
}

void PictureBuilder::macroBlockHandler(cimg_library::CImg<int>* img, Macroblock* macroBlock,
        size_t x, size_t y) {
    // note - Assuming a 4:2:0
    size_t hSize = VideoInformation::getInstance()->getHorizontalSize();
    int* data = img->_data;
    size_t xStop = x + 16;
    size_t yStop = y + 16;
    Block** blocks = macroBlock->getBlocks();
    size_t blockX = 0;
    size_t blockY = 0;
    for (; y < yStop; y++) {
        for (; x < xStop; x++) {
            size_t blockNum = -1;
            if (xStop - x > 8 && yStop - y > 8 && blocks[0]) {
                data[y * hSize + x] =
                        blocks[0]->getFdctransformed()[blockY * 8 + blockX];

            } else if (xStop - x < 8 && yStop - y > 8 && blocks[1]) { // Use Block 2
                data[y * hSize + x] =
                        blocks[1]->getFdctransformed()[blockY * 8 + blockX];

            } else if (xStop - x > 8 && yStop - y < 8 && blocks[2]) { // Use Block 3
                data[y * hSize + x] =
                        blocks[2]->getFdctransformed()[blockY * 8 + blockX];
            } else if (xStop - x < 8 && yStop - y < 8 && blocks[3]) {// Use Block 4
                data[y * hSize + x] =
                        blocks[3]->getFdctransformed()[blockY * 8 + blockX];
            } else { // TODO - make the image colored
                data[y * hSize + x] = 0;
            }
            blockX = (blockX + 1) % 8;
            blockY = blockX == 0 ? blockY + 1 : blockY;
        }
    }
    if (blockX != 0 && blockY != 8) {
        throw VideoException("PictureBuilder::macroBlockHandler failure");
    }
}

void PictureBuilder::updatePositions(size_t *x, size_t* y) {
    *x = (*x + 16) % VideoInformation::getInstance()->getHorizontalSize();
    if (*x == 0) {
        *y = *y + 16;
    }
}
