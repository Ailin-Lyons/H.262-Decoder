//
// Created by elnsa on 2020-01-08.
//

#include "gtest/gtest.h"
#include "../../Util/FileInterface.h"
#include "../../PacketParsers/PASParser.cpp"

TEST(AllTest, PASParser_Test) {
    char relative_path[] = R"(..\..\..\test files/Single Packets/testvideo_noaudio_pas_only.ts)";
    FileInterface::getInstance()->setInstance(relative_path);
    TSPayloadSections::ts_payload_header_fields expected_header = {};
    expected_header.table_id = 0x00;
    expected_header.section_syntax_indicator = 0x01;
    expected_header.t_id_type = TSPayloadSections::TableIDType::program_association_section;
    expected_header.section_length = 0x0D;
    TSPayloadSections::ts_payload_version_section_fields expected_vsf = {};
    expected_vsf.version_number = 0x6;
    expected_vsf.current_next_indicator = 0x1;
    expected_vsf.section_number = 0x0;
    expected_vsf.last_section_number = 0x0;
    ProgramAssociationSection::pas_program expected_pasPrograms = {};
    expected_pasPrograms.program_number = 0x1;
    expected_pasPrograms.assosciated_pid = 0x20;
    ProgramAssociationSection expected = ProgramAssociationSection(expected_header, (unsigned char) 0x9391,
                                                                   expected_vsf, 1, &expected_pasPrograms);
    ProgramAssociationSection *result = PASParser::getPASPacket();
    bool xyz = *result == expected;
    ASSERT_EQ(*result, expected);
}

