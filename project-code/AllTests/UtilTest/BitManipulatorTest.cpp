//
// Created by bhave on 12/18/2019.
//

#include "gtest/gtest.h"
#include "../../Util/BitManipulator.cpp"

TEST(AllTest, Test1) {
    unsigned char testVal[] = {'A', 'F'};
    ASSERT_EQ(4, BitManipulator::ReadNBits(testVal, 4));

}