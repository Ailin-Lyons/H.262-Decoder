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
    this->pasPrograms = pas_program;
    this->transport_stream_id = transport_stream_id;
    this->versionSectionFields = versionSectionFields;
}

void ProgramAssociationSection::print() {
    std::printf("TS_payload_header_fields: \n\t"
                "table_id = %x, t_id_type = program_association_section, section_syntax_indicator %x, section_length = %hx\n"
                "transport_stream_id = %hx\n"
                "TS_payload_version_section_fields \n\t"
                "version_number = %x, current_next_indicator = %x, section_number = %x, last_section_number = %x\n"
                "numPASPrograms = %x\n", headerFields.table_id, headerFields.section_syntax_indicator,
                headerFields.section_length,
                transport_stream_id, versionSectionFields.version_number, versionSectionFields.current_next_indicator,
                versionSectionFields.section_number, versionSectionFields.last_section_number, numPasPrograms);
    if (pasPrograms != nullptr) {
        for (unsigned int i = 0; i < numPasPrograms; i++) {
            std::printf("PAS_Program[%x]: \n\t"
                        "program_number = %hx, associated_pid = %hx\n", i, pasPrograms[i].program_number,
                        pasPrograms[i].assosciated_pid);
        }
    }
}


ProgramAssociationSection::~ProgramAssociationSection() {
    free(this->pasPrograms);//TODO
}

unsigned int ProgramAssociationSection::getProgramPID() {
    if (numPasPrograms > 0) {
        return pasPrograms->assosciated_pid;
    }
    throw PacketException("ProgramAssosciationSection::getProgramPID could not find a video PID");
}

bool ProgramAssociationSection::operator==(const ProgramAssociationSection &rhs) const {
    bool eq = headerFields.t_id_type == rhs.headerFields.t_id_type &&
              headerFields.table_id == rhs.headerFields.table_id &&
              headerFields.section_syntax_indicator == rhs.headerFields.section_syntax_indicator &&
              headerFields.section_length == rhs.headerFields.section_length &&
              transport_stream_id == rhs.transport_stream_id &&
              versionSectionFields.last_section_number == rhs.versionSectionFields.last_section_number &&
              versionSectionFields.section_number == rhs.versionSectionFields.section_number &&
              versionSectionFields.current_next_indicator == rhs.versionSectionFields.current_next_indicator &&
              versionSectionFields.version_number == rhs.versionSectionFields.version_number &&
              numPasPrograms == rhs.numPasPrograms;
    if (!eq) return eq;
    for (int i = 0; i < numPasPrograms; i++) {
        if (pasPrograms[i].assosciated_pid != rhs.pasPrograms[i].assosciated_pid ||
            pasPrograms[i].program_number != rhs.pasPrograms[i].program_number) {
            return false;
        }
    }
    return true;
}

bool ProgramAssociationSection::operator!=(const ProgramAssociationSection &rhs) const {
    return !(rhs == *this);
}
