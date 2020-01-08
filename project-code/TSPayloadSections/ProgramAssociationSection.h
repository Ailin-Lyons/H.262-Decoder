//
// Created by elnsa on 2020-01-05.
//

#ifndef PROJECT_CODE_PROGRAMASSOCIATIONSECTION_H
#define PROJECT_CODE_PROGRAMASSOCIATIONSECTION_H


#include "TSPayloadSections.h"

class ProgramAssociationSection {
public:
    struct pas_program {
        unsigned short program_number; //16-bit
        unsigned short assosciated_pid; // 13-bit this holds either network_PID if program_number==0 else program_map_PID
    };

    ProgramAssociationSection(TSPayloadSections::ts_payload_header_fields tsPayloadHeaderFields, unsigned char transport_stream_id,
                              TSPayloadSections::ts_payload_version_section_fields versionSectionFields, unsigned int numPasPrograms,
                              pas_program* pas_program);

    void print();

private:
    TSPayloadSections::ts_payload_header_fields headerFields{};
    unsigned short transport_stream_id;
    TSPayloadSections::ts_payload_version_section_fields versionSectionFields{};
    unsigned int numPasPrograms;
    pas_program *pasProgram;

};


#endif //PROJECT_CODE_PROGRAMASSOCIATIONSECTION_H
