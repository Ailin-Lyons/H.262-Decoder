//
// Created by elnsa on 2020-01-08.
//

#include "gtest/gtest.h"
#include "../../Util/FileInterface.h"
#include "../../StreamParsers/TransportStreamParsers/PASParser.cpp"
#include "../../StreamParsers/TransportStreamParsers/PMSParser.cpp"

TEST(AllTest, PASPMSParser_Test) {
    char relative_path[] = R"(../../../test files/Single Packets/testvideo_noaudio_PASPMS.ts)";
    FileInterface::getInstance()->setInstance(relative_path);
    TSPayloadSections::ts_payload_header_fields expectedPAS_header = {};
    expectedPAS_header.table_id = 0x00;
    expectedPAS_header.section_syntax_indicator = 0x01;
    expectedPAS_header.t_id_type = TSPayloadSections::TableIDType::program_association_section;
    expectedPAS_header.section_length = 0x0D;
    TSPayloadSections::ts_payload_version_section_fields expectedPAS_vsf = {};
    expectedPAS_vsf.version_number = 0x6;
    expectedPAS_vsf.current_next_indicator = 0x1;
    expectedPAS_vsf.section_number = 0x0;
    expectedPAS_vsf.last_section_number = 0x0;
    auto expected_pasPrograms = (ProgramAssociationSection::pas_program*) malloc(sizeof(ProgramAssociationSection));
    expected_pasPrograms->program_number = 0x1;
    expected_pasPrograms->assosciated_pid = 0x20;
    ProgramAssociationSection PASexpected = ProgramAssociationSection(expectedPAS_header, (unsigned char) 0x9391,
                                                                      expectedPAS_vsf, 1, expected_pasPrograms);
    TSPayloadSections::ts_payload_header_fields expectedPMS_header = {};
    expectedPMS_header.table_id = 0x02;
    expectedPMS_header.section_syntax_indicator = 0x01;
    expectedPMS_header.t_id_type = TSPayloadSections::TableIDType::TS_program_map_section;
    expectedPMS_header.section_length = 0x18;
    TSPayloadSections::ts_payload_version_section_fields expectedPMS_vsf = {};
    expectedPMS_vsf.version_number = 0x1E;
    expectedPMS_vsf.current_next_indicator = 0x1;
    expectedPMS_vsf.section_number = 0x0;
    expectedPMS_vsf.last_section_number = 0x0;
    ProgramMapSection::program_element expected_el = {};
    expected_el.elementary_PID = 0x64;
    expected_el.stream_type_value = 0x02;
    expected_el.stream_type = ProgramMapSection::StreamType::video_H_262;
    expected_el.ES_info_length = 0x06;
    ProgramMapSection PMSexpected = ProgramMapSection(expectedPMS_header, (unsigned short) 1, expectedPMS_vsf,
                                                   (unsigned short) 0x64, (unsigned short) 0, expected_el);
    ESParser::getInstance()->initiateStream();
    ASSERT_EQ(*(ESParser::getInstance()->programMapSection), PMSexpected);
    ASSERT_EQ(*(ESParser::getInstance()->programAssociationSection), PASexpected);
}

