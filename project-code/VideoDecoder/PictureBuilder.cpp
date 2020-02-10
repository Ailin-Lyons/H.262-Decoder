//
// Created by elnsa on 2020-02-08.
//

#include "PictureBuilder.h"
#include "VideoDecoder.h"

cimg_library::CImg<int> *PictureBuilder::makePngFromHPicture(HPicture *picture) {
    if (picture->getState() != HPicture::decoding_state::discrete_cosine_transformed) {
        throw VideoException("PictureBuilder::makePngFromHPicture: received HPicture in incorrect decoding_state");
    }
    VideoInformation *vi = VideoInformation::getInstance();
    cimg_library::CImg<int> *out = new cimg_library::CImg<int>(vi->getHorizontalSize(), vi->getVerticalSize(), 1, 3);
    if (vi->getHorizontalSize() % 16 != 0 || vi->getVerticalSize() % 16 != 0) {
        throw VideoException("PictureBuilder::makePngFromHPicture: invalid resolution");
    }
    size_t horizontalNumMacroblocks = vi->getHorizontalSize() / 16;
    size_t verticalNumMacroblocks = vi->getVerticalSize() / 16;
    for (size_t currBlock = 0; currBlock < (horizontalNumMacroblocks * verticalNumMacroblocks); currBlock++) {
        addMacroblockToCimg(out, getNthMacroblock(picture, currBlock), currBlock);
    }
    return out;
}

Macroblock *PictureBuilder::getNthMacroblock(HPicture *pPicture, size_t n) {
    for (size_t numSlices = 0; numSlices < pPicture->getNumSlices(); numSlices++) {
        Slice *curr = pPicture->getSlices()[numSlices];
        if (n >= curr->getNumMacroblocks()) {
            n -= curr->getNumMacroblocks();
        } else {
            return &curr->getMacroblocks()[n];
        }
    }
    throw VideoException("PictureBuilder::getNthMacroblock: invalid index");
}

void
PictureBuilder::addMacroblockToCimg(cimg_library::CImg<int> *image, Macroblock *macroblock, size_t macroblockNumber) {
    if (VideoInformation::getInstance()->getChromaFormat() != SequenceExtensionPacket::chroma_format_type::cf_420) {
        throw VideoException("PictureBuilder::addMacroblockToCimg: chroma format not handled by decoder");
    }
    size_t h_size = VideoInformation::getInstance()->getHorizontalSize();
    size_t topleft = getTopLeftIndex(macroblockNumber);
    addYBlockToCimg(image, macroblock->getBlocks()[0], topleft);
    addYBlockToCimg(image, macroblock->getBlocks()[1], topleft + 8);
    addYBlockToCimg(image, macroblock->getBlocks()[2], topleft + (8 * h_size));
    addYBlockToCimg(image, macroblock->getBlocks()[3], topleft + (8 * h_size) + 8);
    addCrBlockToCimg(image, macroblock->getBlocks()[4], topleft);
    addCbBlockToCimg(image, macroblock->getBlocks()[5], topleft);
}

void PictureBuilder::addYBlockToCimg(cimg_library::CImg<int> *image, Block *yBlock, size_t topleft) {
    size_t h_size = VideoInformation::getInstance()->getHorizontalSize();
    int *data = image->_data;
    for (size_t y = 0; y < 8; y++) {
        for (size_t x = 0; x < 8; x++) {
            data[topleft + (y * h_size) + x] = yBlock->getFdctransformed()[y * 8 + x];
        }
    }
}

void PictureBuilder::addCrBlockToCimg(cimg_library::CImg<int> *image, Block *crBlock, size_t topleft) {
//TODO
}

void PictureBuilder::addCbBlockToCimg(cimg_library::CImg<int> *image, Block *cbBlock, size_t topleft) {
//TODO
}

size_t PictureBuilder::getTopLeftIndex(size_t number) {
    VideoInformation *vi = VideoInformation::getInstance();
    size_t out = 0;
    while (number > (vi->getHorizontalSize() / 16)) {
        out += 16 * vi->getHorizontalSize();
        number -= (vi->getHorizontalSize() / 16);
    }
    return out + 16 * number;
}
