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
};


TEST_F(BitManipulatorTest, FixtureTest) {
    unsigned char testVal[] = {'A', 'F'};
    ASSERT_EQ(4, BitManipulator::ReadNBits(testVal, 4));
}