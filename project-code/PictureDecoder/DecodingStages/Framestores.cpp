//
// Created by elnsa on 2020-03-01.
//

#include <VideoInformation.h>
#include "Framestores.h"
#include "../../VideoDecoder/VideoException.cpp"

Framestores *Framestores::instance = nullptr;

void Framestores::updateFramestores(HPicture *p) {
    size_t index = 0;
    for (size_t s = 0; s < p->getNumSlices(); s++) {
        Slice *slice = p->getSlices()[s];
        for (size_t m = 0; m < slice->getNumMacroblocks(); m++) {
            Macroblock *mb = slice->getMacroblocks()[m];
            updateFramestoresMacroblock(index, mb);
        }
    }
}

/**
 *  Forms a prediction given a motion vector for a 4:2:0 macroblock
 * @param mv
 * @return a Macroblock or nullptr
 */
Macroblock *Framestores::getPredictionXY(MotionVector *mv) {
    Macroblock::initializerStruct init = {};
    init.block_count = 6;
    init.blocks = (Block **) calloc(6, sizeof(void *));
    size_t int_vec0 = divTruncNeg(mv->getVectorRS0(), 2);
    bool half_flag0 = (mv->getVectorRS0() - (2 * int_vec0)) ? 0 : 1; // NOLINT(modernize-use-bool-literals)
    size_t int_vec1 = divTruncNeg(mv->getVectorRS1(), 2);;
    bool half_flag1 = (mv->getVectorRS1() - (2 * int_vec1)) ? 0 : 1; // NOLINT(modernize-use-bool-literals)
    init.blocks[0] = predictLumBlock(int_vec0, int_vec1, half_flag0, half_flag1);
    init.blocks[1] = predictLumBlock(int_vec0, int_vec1, half_flag0, half_flag1);
    init.blocks[2] = predictLumBlock(int_vec0, int_vec1, half_flag0, half_flag1);
    init.blocks[3] = predictLumBlock(int_vec0, int_vec1, half_flag0, half_flag1);
    init.blocks[4] = predictChromBlock(cr, int_vec0, int_vec1, half_flag0, half_flag1);
    init.blocks[5] = predictChromBlock(cb, int_vec0, int_vec1, half_flag0, half_flag1);
    auto *out = new Macroblock(init);
    return out;
}

size_t Framestores::divTruncNeg(int top, int bottom) {
    if (top < 0) top -= 1;
    return top / bottom;
}

Framestores::Framestores() {
    VideoInformation *vi = VideoInformation::getInstance();
    x_res = vi->getHorizontalSize();
    y_res = vi->getVerticalSize();
    lum = (int *) calloc(x_res * y_res, sizeof(int));
    cr = (int *) calloc((x_res / 2) * (y_res / 2), sizeof(int));
    cb = (int *) calloc((x_res / 2) * (y_res / 2), sizeof(int));
}

Block *Framestores::predictLumBlock(size_t x, size_t y, bool half_x, bool half_y) {
    return nullptr;//TODO
}

Block *Framestores::predictChromBlock(int *arr, size_t x, size_t y, bool half_x, bool half_y) {
    return nullptr;//TODO
}

Framestores::~Framestores() {
    if (lum) free(lum);
    if (cr) free(cr);
    if (cb) free(cb);
}

void Framestores::updateFramestoresMacroblock(size_t index, Macroblock *mb) {
//    size_t chromx = (index*16) //TODO
//    size_t x = (index*64) % x_res;
//    size_t y = (index*64) / x_res;
//    addBlock(lum, x, y, mb->getBlocks()[0]);
//    addBlock(lum, x + 8, y, mb->getBlocks()[0]);
//    addBlock(lum, x, y + 8, mb->getBlocks()[0]);
//    addBlock(lum, x + 8, y + 8, mb->getBlocks()[0]);
//    addBlock(lum, x + 8, y + 8, mb->getBlocks()[0]);
//    addBlock(lum, x + 8, y + 8, mb->getBlocks()[0]);

}
