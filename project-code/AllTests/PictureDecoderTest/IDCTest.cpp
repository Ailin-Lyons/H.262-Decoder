//
// Created by bhave on 3/1/2020.
//

#include "gtest/gtest.h"
#include "../../PictureDecoder/DecodingStages/FCTTransformer.h"
//#include "../../PictureDecoder/DecodingStages/InverseDCTransformer.h"

TEST(AllTest, AllTest_IDCTtest_Test) {
    int pre[64] = {1432, -6, -7, 8, 0, 0, 0, 0, -78, -30, 0, -9, 0, 0, 0, 0, 35, -41, -9, -10, 0, 0, 0, 0, 41, 0, -19,
                   0, 0, 0, 0, 0, 16, 19, 0, 0, 0, 0, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 1};

    int post[64] = {158, 167, 177, 184, 186, 186, 187, 189, 145, 151, 160, 167, 172, 176, 179, 181, 161, 158, 155,
                      154, 157, 161, 165, 167, 189, 180, 170, 164, 163, 163, 161, 159, 193, 189, 186, 185, 186, 181,
                      172, 164, 187, 187, 189, 194, 197, 195, 186, 178, 194, 192, 190, 191, 194, 194, 192, 189, 193,
                      193, 193, 194, 196, 196, 195, 194};


    Block::initializerStruct init = {0, 0, 0, 0, nullptr};
    auto b = new Block(init);
    b->setFquantized(pre);
    FCTTransformer::performIDCTBlockHelper(b);
    auto result = b->getFdctransformed();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ASSERT_EQ(post[i * 8 + j], result[i * 8 + j]);
        }
    }
}
