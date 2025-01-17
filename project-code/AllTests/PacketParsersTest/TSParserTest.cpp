//
// Created by elnsa on 2019-12-20.
//

#include "gtest/gtest.h"
#include "../../StreamParsers/TransportStreamParsers/TSParser.cpp"


TEST(AllTest, TSParser_Test) {
    char relative_path[] = R"(../../../testFiles/Single Packets/single_packet_hasAF.ts)";
    FileInterface *fileInterface = FileInterface::getInstance();
    fileInterface->setInstance(relative_path);
    ASSERT_TRUE(fileInterface->hasNextPacket());
    TransportPacket *actual = TSParser::getNextPacket();
    TransportPacket::transport_header_fields exphead = {};
    exphead.sync_byte = 0x47;
    exphead.transport_error_indicator = 0x0;
    exphead.payload_unit_start_indicator = 0x1;
    exphead.transport_priority = 0x0;
    exphead.pid = 0x64;
    exphead.pid_type = TransportPacket::PID::Misc;
    exphead.transport_scrambling_control = TransportPacket::TSC::NotScrambled;
    exphead.adaptation_field_control = TransportPacket::AFC::AFieldPayload;
    exphead.continuity_counter = 0x0;
    AdaptationField::initializerStruct expaf{};
    expaf.adaptation_field_length = 0x7;
    expaf.discontinuity_indicator = 0x0;
    expaf.random_access_indicator = 0x0;
    expaf.elementary_stream_priority_indicator = 0x0;
    expaf.PCR_flag = 0x1;
    expaf.OPCR_flag = 0x0;
    expaf.splicing_point_flag = 0x0;
    expaf.transport_private_data_flag = 0x0;
    expaf.adaptation_field_extension_flag = 0x0;
    expaf.program_clock_reference = 0x2B5C;
    expaf.original_program_clock_reference = 0x0;
    expaf.splice_countdown = 0x0;
    expaf.transport_private_data_length = 0x0; // transport_private_data is not handled
    expaf.adaptation_field_extension_length = 0x0;
    expaf.ltw_flag = 0x0;
    expaf.piecewise_rate_flag = 0x0;
    expaf.seamless_splice_flag = 0x0;
    expaf.ltw_valid_flag = 0x0;
    expaf.ltw_offset = 0x0;
    expaf.piecewise_rate = 0x0;
    expaf.splice_type = AdaptationField::ST::splice_decoding_delay_other;
    expaf.DTS_next_AU = 0x0;
    unsigned char expdata[176] = {0x00, 0x00, 0x01, 0xE0, 0x00, 0x00, 0x84, 0x80, 0x05, 0x21, 0x00, 0x03, 0x19, 0x41,
                                  0x00, 0x00, 0x01, 0xB3, 0x50, 0x02, 0xD0, 0x33, 0x01, 0xF4, 0x26, 0x20, 0x00, 0x00,
                                  0x01, 0xB5, 0x14, 0x6A, 0x00, 0x01, 0x00, 0x80, 0x00, 0x00, 0x01, 0xB5, 0x2B, 0x05,
                                  0x01, 0x05, 0x14, 0x02, 0x16, 0x80, 0x00, 0x00, 0x01, 0xB8, 0x00, 0x08, 0x00, 0x40,
                                  0x00, 0x00, 0x01, 0x00, 0x00, 0x0F, 0xFF, 0xF8, 0x00, 0x00, 0x01, 0xB5, 0x8F, 0xFF,
                                  0xF3, 0x41, 0x80, 0x00, 0x00, 0x01, 0x01, 0x1B, 0xF6, 0x7C, 0x03, 0x32, 0x61, 0x37,
                                  0xE0, 0x1B, 0x93, 0x10, 0xFC, 0xF4, 0xA1, 0x44, 0xEB, 0x22, 0x09, 0x9F, 0xA3, 0x70,
                                  0x13, 0x74, 0x30, 0x12, 0xFD, 0x89, 0xEB, 0xB7, 0x10, 0xC0, 0x1D, 0x00, 0xEF, 0x67,
                                  0x42, 0x1C, 0x3E, 0xB9, 0x1C, 0x0A, 0x80, 0xE9, 0x2A, 0x1A, 0x8E, 0x3A, 0xE1, 0xB7,
                                  0xBE, 0x48, 0x0D, 0xC3, 0x12, 0x05, 0x89, 0xA8, 0x49, 0x49, 0x16, 0x70, 0x77, 0xAC,
                                  0x26, 0x80, 0xEB, 0x92, 0x50, 0xDF, 0x5A, 0x03, 0x00, 0x2F, 0x1A, 0x10, 0x43, 0x46,
                                  0x48, 0xB3, 0x6C, 0x41, 0x84, 0xD4, 0x7D, 0x80, 0xC2, 0x43, 0xBC, 0x45, 0xDA, 0x52,
                                  0x4B, 0x26, 0x1C, 0xAB, 0x9A, 0x03, 0xA0, 0x18};
    TransportPacket* expected = new TransportPacket(exphead, AdaptationField(expaf), (unsigned int) 176, (unsigned char *) &expdata);
    bool bla = *actual == *expected;
    std::printf("%x\n",bla);
    ASSERT_EQ(*actual, *expected);
    free(actual);
    free(expected);
}
