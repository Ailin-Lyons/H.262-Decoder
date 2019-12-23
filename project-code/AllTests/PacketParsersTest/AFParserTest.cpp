//
// Created by elnsa on 2019-12-20.
//

#include "gtest/gtest.h"
#include "../../PacketParsers/AFParser.cpp"
#include "../../TransportPacketStructure/AdaptationField.h"

TEST(AllTest, AFParser_Test) {
    unsigned char testVal[] = {0x07, 0x10, 0x00, 0x00, 0x00, 0x12, 0xFE, 0x00, 0x00, 0x00, 0x01, 0xE0};
    AdaptationField af = AFParser::generateAdaptationField(testVal);
    ASSERT_EQ(0x7, af.adaptation_field_length);
    ASSERT_EQ(0x0, af.discontinuity_indicator);
    ASSERT_EQ(0x0, af.random_access_indicator);
    ASSERT_EQ(0x0, af.elementary_stream_priority_indicator);
    ASSERT_EQ(0x1, af.PCR_flag);
    ASSERT_EQ(0x0, af.OPCR_flag);
    ASSERT_EQ(0x0, af.splicing_point_flag);
    ASSERT_EQ(0x0, af.transport_private_data_flag);
    ASSERT_EQ(0x0, af.adaptation_field_extension_flag);
    ASSERT_EQ(0x2B5C, af.program_clock_reference);
    ASSERT_EQ(0x0, af.original_program_clock_reference);
    ASSERT_EQ(0x0, af.splice_countdown);
    ASSERT_EQ(0x0, af.transport_private_data_length);
    ASSERT_EQ(0x0, af.adaptation_field_extension_length);
    ASSERT_EQ(0x0, af.ltw_flag);
    ASSERT_EQ(0x0, af.piecewise_rate_flag);
    ASSERT_EQ(0x0, af.seamless_splice_flag);
    ASSERT_EQ(0x0, af.ltw_offset);
    ASSERT_EQ(0x0, af.piecewise_rate);
    ASSERT_EQ(0x0, af.DTS_next_AU);
}

TEST(AllTest, AFParserAllFieldsSet) {
    unsigned char testVal[] = {0x1E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xAE,
                               0x02, 0xEE, 0xEE, 0x0C, 0xFF, 0xC0, 0x01, 0x2A, 0xAA, 0xAA, 0x6F, 0xFF, 0xFF, 0xFF, 0xFF,
                               0xFF, 0xFF};
    AdaptationField af = AFParser::generateAdaptationField(testVal);
    ASSERT_EQ(0x1E, af.adaptation_field_length);
    ASSERT_EQ(0x1, af.discontinuity_indicator);
    ASSERT_EQ(0x1, af.random_access_indicator);
    ASSERT_EQ(0x1, af.elementary_stream_priority_indicator);
    ASSERT_EQ(0x1, af.PCR_flag);
    ASSERT_EQ(0x1, af.OPCR_flag);
    ASSERT_EQ(0x1, af.splicing_point_flag);
    ASSERT_EQ(0x1, af.transport_private_data_flag);
    ASSERT_EQ(0x1, af.adaptation_field_extension_flag);
    ASSERT_EQ(0x258000000D3, af.program_clock_reference);
    ASSERT_EQ(0x258000000D3, af.original_program_clock_reference);
    ASSERT_EQ(0xAE, af.splice_countdown);
    ASSERT_EQ(0x2, af.transport_private_data_length);
    ASSERT_EQ(0x0C, af.adaptation_field_extension_length);
    ASSERT_EQ(0x1, af.ltw_flag);
    ASSERT_EQ(0x1, af.piecewise_rate_flag);
    ASSERT_EQ(0x1, af.seamless_splice_flag);
    ASSERT_EQ(0x1, af.ltw_valid_flag);
    ASSERT_EQ(0x4001, af.ltw_offset);
    ASSERT_EQ(0x2AAAAA, af.piecewise_rate);
    ASSERT_EQ(0x1FFFFFFFF, af.DTS_next_AU);
}
