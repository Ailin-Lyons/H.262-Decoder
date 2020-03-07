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
            index++;
        }
    }
}

/**
 *  Forms a prediction given a motion vector for a 4:2:0 macroblock
 * @param mv
 * @return a Macroblock or nullptr
 */
Macroblock *Framestores::getPredictionXY(int macroblock_index, MotionVector *mv) {
    Macroblock::initializerStruct init = {};
    init.block_count = 6;
    init.blocks = (Block **) calloc(6, sizeof(void *));
    int int_vec0 = div2TruncNeg(mv->getVectorRS0());
    bool half_flag0 = (mv->getVectorRS0() - (2 * int_vec0)) ? 0 : 1; // NOLINT(modernize-use-bool-literals)
    int int_vec1 = div2TruncNeg(mv->getVectorRS1());
    bool half_flag1 = (mv->getVectorRS1() - (2 * int_vec1)) ? 0 : 1; // NOLINT(modernize-use-bool-literals)

    int x_index = macroblock_index % (x_res / 16);
    int y_index = macroblock_index / (x_res / 16);

    int lum_base_x = x_index * 16 + int_vec0;
    int lum_base_y = y_index * 16 + int_vec1;

    int chrom_vec_0 = div2TruncNeg(mv->getVectorRS0() / 2);
    bool chrom_half_flag0 = ((mv->getVectorRS0() / 2) - (2 * chrom_vec_0)) ? 0 : 1;
    int chrom_vec_1 = div2TruncNeg(mv->getVectorRS1() / 2);
    bool chrom_half_flag1 = ((mv->getVectorRS1() / 2) - (2 * chrom_vec_1)) ? 0 : 1;

    int chrom_base_x = x_index * 8 + chrom_vec_0;
    int chrom_base_y = y_index * 8 + chrom_vec_1;

    init.blocks[0] = predictBlock(0, lum, x_res, y_res, lum_base_x, lum_base_y, half_flag0, half_flag1);
    init.blocks[1] = predictBlock(1, lum, x_res, y_res, lum_base_x + 8, lum_base_y, half_flag0, half_flag1);
    init.blocks[2] = predictBlock(2, lum, x_res, y_res, lum_base_x, lum_base_y + 8, half_flag0, half_flag1);
    init.blocks[3] = predictBlock(3, lum, x_res, y_res, lum_base_x + 8, lum_base_y + 8, half_flag0, half_flag1);
    init.blocks[4] = predictBlock(4, cb, x_res / 2, y_res / 2, chrom_base_x, chrom_base_y, chrom_half_flag0,
                                  chrom_half_flag1);
    init.blocks[5] = predictBlock(5, cr, x_res / 2, y_res / 2, chrom_base_x, chrom_base_y, chrom_half_flag0,
                                  chrom_half_flag1);
    auto *out = new Macroblock(init);
    return out;
}

Framestores::Framestores() {
    VideoInformation *vi = VideoInformation::getInstance();
    x_res = vi->getHorizontalSize();
    y_res = vi->getVerticalSize();
    lum = (int *) calloc(x_res * y_res, sizeof(int));
    cb = (int *) calloc((x_res / 2) * (y_res / 2), sizeof(int));
    cr = (int *) calloc((x_res / 2) * (y_res / 2), sizeof(int));
}

Block *Framestores::predictBlock(size_t block_index, const int *arr, size_t width, size_t height,
                                 int x_base, int y_base, bool half_x, bool half_y) {
    auto *out = new Block(Block::initializerStruct{block_index, Block::calculateCC(block_index)});
    out->setData((int *) calloc(64, sizeof(int)));

    if (x_base + 7 + 1 >= width)half_x = false;
    if (y_base + 7 + 1 >= height)half_y = false;

    for (size_t y = 0; y < 8; y++) {
        for (size_t x = 0; x < 8; x++) {
            int *data = out->getData();
            if (!half_x && !half_y) {
                data[y * 8 + x] = arr[((y_base + y) * width) + x_base + x];
            } else if (!half_x) {
                data[y * 8 + x] = div2Round(arr[((y_base + y) * width) + x_base + x]
                                            + arr[((y_base + y + 1) * width) + x_base + x]);
            } else if (!half_y) {
                data[y * 8 + x] = div2Round(arr[((y_base + y) * width) + x_base + x]
                                            + arr[((y_base + y) * width) + x_base + x + 1]);
            } else {
                data[y * 8 + x] = div4Round(arr[((y_base + y) * width) + x_base + x]
                                            + arr[((y_base + y) * width) + x_base + x + 1]
                                            + arr[((y_base + y + 1) * width) + x_base + x]
                                            + arr[((y_base + y + 1) * width) + x_base + x + 1]);
            }
        }
    }
    return out;
}

Framestores::~Framestores() {
    if (lum) free(lum);
    if (cb) free(cb);
    if (cr) free(cr);
}

void Framestores::updateFramestoresMacroblock(size_t index, Macroblock *mb) {
    size_t x_index = index % (x_res / 16);
    size_t y_index = index / (x_res / 16);
    addBlock(lum, x_res, x_index * 16, y_index * 16, mb->getBlocks()[0]);
    addBlock(lum, x_res, x_index * 16 + 8, y_index * 16, mb->getBlocks()[1]);
    addBlock(lum, x_res, x_index * 16, y_index * 16 + 8, mb->getBlocks()[2]);
    addBlock(lum, x_res, x_index * 16 + 8, y_index * 16 + 8, mb->getBlocks()[3]);
    addBlock(cb, x_res / 2, x_index * 8, y_index * 8, mb->getBlocks()[4]);
    addBlock(cr, x_res / 2, x_index * 8, y_index * 8, mb->getBlocks()[5]);
}

void Framestores::addBlock(int *targetArray, size_t width, size_t x_base, size_t y_base, Block *toAdd) {
    for (size_t y = 0; y < 8; y++) {
        for (size_t x = 0; x < 8; x++) {
            targetArray[((y_base + y) * width) + (x_base + x)] = toAdd->getData()[y * 8 + x];
        }
    }
}

/**
 * H.262 "DIV" operator
 */
int Framestores::div2TruncNeg(int numerator) {
    if (numerator < 0) numerator -= 1;
    return numerator / 2;
}

/**
 * H.262 "//" operator
 */
int Framestores::div2Round(int numerator) {
    if (numerator > 0 && numerator % 2 == 1) return numerator / 2 + 1;
    if (numerator < 0 && numerator % 2 == -1) return numerator / 2 - 1;
    return numerator / 2;
}

/**
 * H.262 "//" operator
 */
int Framestores::div4Round(int numerator) {
    if (numerator > 0 && numerator % 4 > 1) return numerator / 4 + 1;
    if (numerator < 0 && numerator % 4 < -1) return numerator / 4 - 1;
    return numerator / 4;
}
