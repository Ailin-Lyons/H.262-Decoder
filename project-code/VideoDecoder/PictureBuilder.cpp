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
    auto *out = new cimg_library::CImg<int>(vi->getHorizontalSize(), vi->getVerticalSize(), 1,3);
    if (vi->getHorizontalSize() % 16 != 0 || vi->getVerticalSize() % 16 != 0) {
        throw VideoException("PictureBuilder::makePngFromHPicture: invalid resolution");
    }
    size_t horizontalNumMacroblocks = (size_t) vi->getHorizontalSize() / 16;
    size_t verticalNumMacroblocks = (size_t) vi->getVerticalSize() / 16;
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
    throw VideoException("PictureBuilder::getNthMacroblock: picture is missing macroblocks");
}

void
PictureBuilder::addMacroblockToCimg(cimg_library::CImg<int> *image, Macroblock *macroblock, size_t macroblockNumber) {
    if (VideoInformation::getInstance()->getChromaFormat() != SequenceExtensionPacket::chroma_format_type::cf_420) {
        throw VideoException("PictureBuilder::addMacroblockToCimg: chroma format not handled by decoder");
    }
    size_t h_size = VideoInformation::getInstance()->getHorizontalSize();
    size_t topLeft = getTopLeftIndex(macroblockNumber);
    if (macroblock->getBlocks()[0]) addYBlockToCimg(image, macroblock->getBlocks()[0], topLeft);
    if (macroblock->getBlocks()[1]) addYBlockToCimg(image, macroblock->getBlocks()[1], topLeft + 8);
    if (macroblock->getBlocks()[2]) addYBlockToCimg(image, macroblock->getBlocks()[2], topLeft + (8 * h_size));
    if (macroblock->getBlocks()[3]) addYBlockToCimg(image, macroblock->getBlocks()[3], topLeft + (8 * h_size) + 8);
    if (macroblock->getBlocks()[4]) addCbBlockToCimg(image, macroblock->getBlocks()[4], topLeft);
    if (macroblock->getBlocks()[5]) addCrBlockToCimg(image, macroblock->getBlocks()[5], topLeft);
}

void PictureBuilder::addYBlockToCimg(cimg_library::CImg<int> *image, Block *yBlock, size_t topLeft) {
    size_t h_size = VideoInformation::getInstance()->getHorizontalSize();
    int *data = image->_data;
    for (size_t y = 0; y < 8; y++) {
        for (size_t x = 0; x < 8; x++) {
            data[topLeft + (y * h_size) + x] = yBlock->getFdctransformed()[y * 8 + x];
        }
    }
}

void PictureBuilder::addCbBlockToCimg(cimg_library::CImg<int> *image, Block *bBlock, size_t topLeft) {
    VideoInformation *vi = VideoInformation::getInstance();
    size_t h_size = vi->getHorizontalSize();
    int *data = image->_data;
    size_t cr = vi->getHorizontalSize() * vi->getVerticalSize();
    for (size_t y = 0; y < 8; y++) {
        for (size_t x = 0; x < 8; x++) {
            data[topLeft + (2 * y * h_size) + (2 * x) + cr] = bBlock->getFdctransformed()[y * 8 + x];
            data[topLeft + (2 * y * h_size) + (2 * x) + cr + 1] = bBlock->getFdctransformed()[y * 8 + x];
            data[topLeft + (2 * y * h_size) + (2 * x) + cr + h_size] = bBlock->getFdctransformed()[y * 8 + x];
            data[topLeft + (2 * y * h_size) + (2 * x) + cr + h_size + 1] = bBlock->getFdctransformed()[y * 8 + x];
        }
    }
}

void PictureBuilder::addCrBlockToCimg(cimg_library::CImg<int> *image, Block *rBlock, size_t topLeft) {
    VideoInformation *vi = VideoInformation::getInstance();
    size_t h_size = vi->getHorizontalSize();
    int *data = image->_data;
    size_t cb = (size_t) 2 * vi->getHorizontalSize() * vi->getVerticalSize();
    for (size_t y = 0; y < 8; y++) {
        for (size_t x = 0; x < 8; x++) {
            data[topLeft + (2 * y * h_size) + (2 * x) + cb] = rBlock->getFdctransformed()[y * 8 + x];
            data[topLeft + (2 * y * h_size) + (2 * x) + cb + 1] = rBlock->getFdctransformed()[y * 8 + x];
            data[topLeft + (2 * y * h_size) + (2 * x) + cb + h_size] = rBlock->getFdctransformed()[y * 8 + x];
            data[topLeft + (2 * y * h_size) + (2 * x) + cb + h_size + 1] = rBlock->getFdctransformed()[y * 8 + x];
        }
    }
}

size_t PictureBuilder::getTopLeftIndex(size_t number) {
    VideoInformation *vi = VideoInformation::getInstance();
    size_t out = 0;
    while (number >= (vi->getHorizontalSize() / 16)) {
        out += 16 * vi->getHorizontalSize();
        number -= (vi->getHorizontalSize() / 16);
    }
    return out + 16 * number;
}
