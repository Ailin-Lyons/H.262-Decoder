//
// Created by bhave on 12/18/2019.
//

#include "gtest/gtest.h"
#include "../../Util/BitManipulator.cpp"


/**
 * BitManipulator Test Fixture Class
 */
class BitManipulatorTest : public ::testing::Test {
protected:

    unsigned char testVal0[2] = {'A', 'F'};
    unsigned char testVal1[8] = {'H', 'E', 'L', 'L', 'O', 'M', 'E', 'N'};
    unsigned char testVal2[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                                  'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
                                  'X', 'Y', 'Z'};
};


TEST_F(BitManipulatorTest, BasicTest) {
    ASSERT_EQ(4, BitManipulator::readNBits(testVal0, 4));
}

TEST_F(BitManipulatorTest, OffsetTest) {
    auto readVal = (long long *) malloc(sizeof(long long) * 8);
    // read the offset byte at the the correct offset
    for (unsigned int i = 0; i < 8; i++) {
        readVal[i] = BitManipulator::readNBitsOffset(testVal1 + i, i, 8 - i);
    }
    ASSERT_EQ(readVal[0], testVal1[0]);
    ASSERT_EQ(readVal[1], testVal1[1] & 0x7f);
    ASSERT_EQ(readVal[2], testVal1[2] & 0x3f);
    ASSERT_EQ(readVal[3], testVal1[3] & 0x1f);
    ASSERT_EQ(readVal[4], testVal1[4] & 0xf);
    ASSERT_EQ(readVal[5], testVal1[5] & 0x7);
    ASSERT_EQ(readVal[6], testVal1[6] & 0x3);
    ASSERT_EQ(readVal[7], testVal1[7] & 0x1);
    free(readVal);
}

TEST_F(BitManipulatorTest, readMoreThan64) {
    long long readVal = BitManipulator::readNBits(testVal2, 16 * 8);
    ASSERT_EQ(readVal, 0x494a4b4c4d4e4f50);
    readVal = BitManipulator::readNBits(testVal2, 9 * 8 + 4);
    ASSERT_EQ(readVal, 0x2434445464748494);
}