//
// Created by elnsa on 2020-01-05.
//

#include "ProgramAssociationSection.h"

ProgramAssociationSection::ProgramAssociationSection(
        TSPayloadSections::ts_payload_header_fields tsPayloadHeaderFields, unsigned char transport_stream_id,
        TSPayloadSections::ts_payload_version_section_fields versionSectionFields, unsigned int numPasPrograms,
        ProgramAssociationSection::pas_program *pas_program) {

    this->headerFields = tsPayloadHeaderFields;
    this->numPasPrograms = numPasPrograms;
    this->pasProgram = pas_program;
    this->transport_stream_id = transport_stream_id;
    this->versionSectionFields = versionSectionFields;
}

void ProgramAssociationSection::print() {
    std::printf("TS_payload_header_fields: \n\t"
                "table_id = %u, t_id_type = program_association_section, section_syntax_indicator %u, section_length = %hu\n"
                "transport_stream_id = %hu\n"
                "TS_payload_version_section_fields \n\t"
                "version_number = %u, current_next_indicator = %u, section_number = %u, last_section_number = %u\n"
                "numPASPrograms = %u\n", headerFields.table_id, headerFields.section_syntax_indicator, headerFields.section_length,
                transport_stream_id, versionSectionFields.version_number, versionSectionFields.current_next_indicator,
                versionSectionFields.section_number, versionSectionFields.last_section_number, numPasPrograms);
    if (pasProgram != nullptr) {
        for (unsigned int i = 0; i < numPasPrograms; i++) {
            std::printf("PAS_Program[%u]: \n\t"
                        "program_number = %hu, associated_pid = %hu\n", i, pasProgram[i].program_number, pasProgram[i].assosciated_pid);
        }
    }
}
