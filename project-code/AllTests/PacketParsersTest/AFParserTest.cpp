//
// Created by elnsa on 2019-12-20.
//

#include "gtest/gtest.h"
#include "../../PacketParsers/AFParser.cpp"

TEST(AllTest, AFParser_Test) {
    unsigned char testVal[] = {0x07, 0x10, 0x00, 0x00, 0x00, 0x12, 0xFE, 0x00, 0x00, 0x00, 0x01, 0xE0};
    AdaptationField actual = AFParser::generateAdaptationField(testVal);
    AdaptationField::initializerStruct expected{};
    expected.adaptation_field_length = 0x7;
    expected.discontinuity_indicator = 0x0;
    expected.random_access_indicator = 0x0;
    expected.elementary_stream_priority_indicator = 0x0;
    expected.PCR_flag = 0x1;
    expected.OPCR_flag = 0x0;
    expected.splicing_point_flag = 0x0;
    expected.transport_private_data_flag = 0x0;
    expected.adaptation_field_extension_flag = 0x0;
    expected.program_clock_reference = 0x2B5C;
    expected.original_program_clock_reference = 0x0;
    expected.splice_countdown = 0x0;
    expected.transport_private_data_length = 0x0;
    expected.adaptation_field_extension_length = 0x0;
    expected.ltw_offset = 0x0;
    expected.piecewise_rate = 0x0;
    expected.DTS_next_AU = 0x0;
    ASSERT_EQ(actual, AdaptationField(expected));
}

TEST(AllTest, AFParserAllFieldsSet) {
    unsigned char testVal[] = {0x1E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xAE,
                               0x02, 0xEE, 0xEE, 0x0C, 0xFF, 0xC0, 0x01, 0x2A, 0xAA, 0xAA, 0x6F, 0xFF, 0xFF, 0xFF, 0xFF,
                               0xFF, 0xFF};
    AdaptationField actual = AFParser::generateAdaptationField(testVal);
    AdaptationField::initializerStruct expected{};
    expected.adaptation_field_length = 0x1E;
    expected.discontinuity_indicator = 0x1;
    expected.random_access_indicator = 0x1;
    expected.elementary_stream_priority_indicator = 0x1;
    expected.PCR_flag = 0x1;
    expected.OPCR_flag = 0x1;
    expected.splicing_point_flag = 0x1;
    expected.transport_private_data_flag = 0x1;
    expected.adaptation_field_extension_flag = 0x1;
    expected.program_clock_reference = 0x258000000D3;
    expected.original_program_clock_reference = 0x258000000D3;
    expected.splice_countdown = 0xAE;
    expected.transport_private_data_length = 0x2;
    expected.adaptation_field_extension_length = 0x0C;
    expected.ltw_flag = 0x1;
    expected.ltw_valid_flag = 0x1;
    expected.piecewise_rate_flag = 0x1;
    expected.seamless_splice_flag = 0x1;
    expected.ltw_offset = 0x4001;
    expected.piecewise_rate = 0x2AAAAA;
    expected.DTS_next_AU = 0x1FFFFFFFF;
    ASSERT_EQ(actual, AdaptationField(expected));
}
