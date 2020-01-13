//
// Created by elnsa on 2020-01-05.
//

#include "ProgramMapSection.h"
#include "TSPayloadSections.h"

ProgramMapSection::ProgramMapSection(TSPayloadSections::ts_payload_header_fields hfs, unsigned short prognum,
                                     TSPayloadSections::ts_payload_version_section_fields vsf, unsigned short pcrpid,
                                     unsigned short pi_length, ProgramMapSection::program_element progels) {
    headerFields = hfs;
    program_number = prognum;
    versionSectionFields = vsf;
    PCR_PID = pcrpid;
    program_info_length = pi_length;
    video_stream_element = progels;
}

void ProgramMapSection::print() {
    std::printf(
            "ProgramMapSection:\n\ttable_id: %hhx, ssi: %hhx, section_length: %x, prognum: %hx, version: %hhx, currnext: %hhx, section: %hhx, last_section: %hhx, PCR_PID: %hx, pi_length: %hx\n",
            headerFields.table_id, headerFields.section_syntax_indicator, headerFields.section_length, program_number,
            versionSectionFields.version_number, versionSectionFields.current_next_indicator,
            versionSectionFields.section_number, versionSectionFields.last_section_number, PCR_PID,
            program_info_length);
    std::printf("\tVideo stream elements:\n");
    std::printf("\tType: %x, PID: %hhx\n", video_stream_element.stream_type, video_stream_element.elementary_PID);
}

unsigned int ProgramMapSection::getVideoStreamPID() {
    return video_stream_element.elementary_PID;
}

bool ProgramMapSection::operator==(const ProgramMapSection &rhs) const {
    return headerFields.t_id_type == rhs.headerFields.t_id_type &&
           headerFields.table_id == rhs.headerFields.table_id &&
           headerFields.section_syntax_indicator == rhs.headerFields.section_syntax_indicator &&
           headerFields.section_length == rhs.headerFields.section_length &&
           program_number == rhs.program_number &&
           versionSectionFields.last_section_number == rhs.versionSectionFields.last_section_number &&
           versionSectionFields.section_number == rhs.versionSectionFields.section_number &&
           versionSectionFields.current_next_indicator == rhs.versionSectionFields.current_next_indicator &&
           versionSectionFields.version_number == rhs.versionSectionFields.version_number &&
           PCR_PID == rhs.PCR_PID &&
           program_info_length == rhs.program_info_length &&
           video_stream_element.stream_type_value == rhs.video_stream_element.stream_type_value &&
           video_stream_element.stream_type == rhs.video_stream_element.stream_type &&
           video_stream_element.elementary_PID == rhs.video_stream_element.elementary_PID &&
           video_stream_element.ES_info_length == rhs.video_stream_element.ES_info_length;
}

bool ProgramMapSection::operator!=(const ProgramMapSection &rhs) const {
    return !(rhs == *this);
};
