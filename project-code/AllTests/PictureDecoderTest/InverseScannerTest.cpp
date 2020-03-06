//
// Created by elnsa on 2020-01-30.
//
#include "gtest/gtest.h"
#include "../../PictureDecoder/DecodingStages/InverseScanner.h"
#include "../../PictureDecoder/Slice/Block.h"

TEST(AllTest, AllTest_InverseScanner_Test) {
    int pre[64] = {0, 1, 2, 3, 4, 5, 6, 7,
                   8, 9, 10, 11, 12, 13, 14, 15,
                   16, 17, 18, 19, 20, 21, 22, 23,
                   24, 25, 26, 27, 28, 29, 30, 31,
                   32, 33, 34, 35, 36, 37, 38, 39,
                   40, 41, 42, 43, 44, 45, 46, 47,
                   48, 49, 50, 51, 52, 53, 54, 55,
                   56, 57, 58, 59, 60, 61, 62, 63};

    int post[8][8] = {{0,  1,  5,  6,  14, 15, 27, 28},
                      {2,  4,  7,  13, 16, 26, 29, 42},
                      {3,  8,  12, 17, 25, 30, 41, 43},
                      {9,  11, 18, 24, 31, 40, 44, 53},
                      {10, 19, 23, 32, 39, 45, 52, 54},
                      {20, 22, 33, 38, 46, 51, 55, 60},
                      {21, 34, 37, 47, 50, 56, 59, 61},
                      {35, 36, 48, 49, 57, 58, 62, 63}};

    Block::initializerStruct init = {0, 0, 0, 0, pre};
    Block *b = new Block(init);
    InverseScanner::performInverseScanHelper(b);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ASSERT_EQ(post[i][j], b->getData()[i * 8 + j]);
        }
    }
}
