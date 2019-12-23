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
    void SetUp() override {
        //TODO - setup mock testing values

    }

    unsigned char testVal0[2] = {'A', 'F'};
    unsigned char testVal1[] = {};
    unsigned char testVal2[] = {};
    unsigned char testVal3[] = {};
    unsigned char testVal4[] = {};
    unsigned char testVal5[] = {};
};


TEST_F(BitManipulatorTest, FixtureTest) {
    ASSERT_EQ(4, BitManipulator::ReadNBits(testVal0, 4));
}