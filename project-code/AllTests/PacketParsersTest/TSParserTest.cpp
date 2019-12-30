//
// Created by elnsa on 2019-12-20.
//

#include "gtest/gtest.h"
#include "../../PacketParsers/TSParser.cpp"

TEST(AllTest, TSParser_Test) {
    char relative_path[] = R"(..\..\..\test files\single_packet_hasAF.ts)";
    FileInterface* fileInterface = FileInterface::getInstance();
    fileInterface->setInstance(relative_path);
    ASSERT_TRUE(fileInterface->HasNextPacket());
    TransportPacket* pack = TSParser::GetNextPacket();
    ASSERT_EQ(0x47,pack->header_fields.sync_byte);
    ASSERT_EQ(0x0,pack->header_fields.transport_error_indicator);
    ASSERT_EQ(0x1,pack->header_fields.payload_unit_start_indicator);
    ASSERT_EQ(0x0,pack->header_fields.transport_priority);
    ASSERT_EQ(TransportPacket::PID::Misc,pack->header_fields.pid);
    ASSERT_EQ(TransportPacket::TSC::NotScrambled,pack->header_fields.transport_scrambling_control);
    ASSERT_EQ(TransportPacket::AFC::AFieldPayload,pack->header_fields.adaptation_field_control);
    ASSERT_EQ(0x0,pack->header_fields.continuity_counter);
    ASSERT_EQ(0x7, pack->adaptationField.adaptation_field_length);
    ASSERT_EQ(0x0, pack->adaptationField.discontinuity_indicator);
    ASSERT_EQ(0x0, pack->adaptationField.random_access_indicator);
    ASSERT_EQ(0x0, pack->adaptationField.elementary_stream_priority_indicator);
    ASSERT_EQ(0x1, pack->adaptationField.PCR_flag);
    ASSERT_EQ(0x0, pack->adaptationField.OPCR_flag);
    ASSERT_EQ(0x0, pack->adaptationField.splicing_point_flag);
    ASSERT_EQ(0x0, pack->adaptationField.transport_private_data_flag);
    ASSERT_EQ(0x0, pack->adaptationField.adaptation_field_extension_flag);
    ASSERT_EQ(0x2B5C, pack->adaptationField.program_clock_reference);
    ASSERT_EQ(0x0, pack->adaptationField.original_program_clock_reference);
    ASSERT_EQ(0x0, pack->adaptationField.splice_countdown);
    ASSERT_EQ(0x0, pack->adaptationField.transport_private_data_length);
    ASSERT_EQ(0x0, pack->adaptationField.adaptation_field_extension_length);
    ASSERT_EQ(0x0, pack->adaptationField.ltw_flag);
    ASSERT_EQ(0x0, pack->adaptationField.piecewise_rate_flag);
    ASSERT_EQ(0x0, pack->adaptationField.seamless_splice_flag);
    ASSERT_EQ(0x0, pack->adaptationField.ltw_offset);
    ASSERT_EQ(0x0, pack->adaptationField.piecewise_rate);
    ASSERT_EQ(0x0, pack->adaptationField.DTS_next_AU);
    free(pack);
}
