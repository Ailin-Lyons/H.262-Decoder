//
// Created by elnsa on 2020-01-05.
//

#include "ProgramMapSection.h"
#include "TSPayloadSections.h"

ProgramMapSection::ProgramMapSection(TSPayloadSections::ts_payload_header_fields hfs, unsigned short prognum,
                                     TSPayloadSections::ts_payload_version_section_fields vsf, unsigned short pcrpid,
                                     unsigned short pi_length, Descriptor::decriptor_struct proginf,
                                     ProgramMapSection::program_element progels) {
    headerFields = hfs;
    program_number = prognum;
    versionSectionFields = vsf;
    PCR_PID = pcrpid;
    program_info_length = pi_length;
    program_info_descriptors = proginf;
    video_stream_element = progels;
}

void ProgramMapSection::print() {
    std::printf(
            "ProgramMapSection:\n\ttable_id: %hhx, ssi: %hhx, section_length: %x, prognum: %hx, version: %hhx, currnext: %hhx, section: %hhx, last_section: %hhx, PCR_PID: %hx, pi_length: %hx\n",
            headerFields.table_id,headerFields.section_syntax_indicator,headerFields.section_length,program_number,versionSectionFields.version_number,versionSectionFields.current_next_indicator,versionSectionFields.section_number,versionSectionFields.last_section_number,PCR_PID,program_info_length);
    for(int i = 0; i < program_info_descriptors.numDescriptorsKept; i++){
        program_info_descriptors.descriptors->print();
    }
    std::printf("\tVideo stream elements:\n");
    std::printf("\tType: %x, PID: %hhx\n",video_stream_element.stream_type,video_stream_element.elementary_PID);
    for(int i = 0; i < video_stream_element.descriptors.numDescriptorsKept; i++){
        video_stream_element.descriptors.descriptors->print();
    }
}

unsigned int ProgramMapSection::getVideoStreamPID(){
    return video_stream_element.elementary_PID;
};
