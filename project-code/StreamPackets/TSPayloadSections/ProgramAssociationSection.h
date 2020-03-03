//
// Created by elnsa on 2020-01-05.
//

#ifndef PROJECT_CODE_PROGRAMASSOCIATIONSECTION_H
#define PROJECT_CODE_PROGRAMASSOCIATIONSECTION_H


#include "TSPayloadSections.h"

/**
 * H.222.0 Table 2-25
 */
class ProgramAssociationSection {
public:

    /**
     * The PAS contains a list of all available program. Each program is represented by this struct
     */
    struct pas_program {
        unsigned short program_number; //16-bit
        unsigned short assosciated_pid; // 13-bit this holds either network_PID if program_number==0 else program_map_PID
    };

    ProgramAssociationSection(TSPayloadSections::ts_payload_header_fields tsPayloadHeaderFields,
                              unsigned short transport_stream_id,
                              TSPayloadSections::ts_payload_version_section_fields versionSectionFields,
                              size_t numPasPrograms,
                              pas_program *pas_program);

    ~ProgramAssociationSection();

    void print();

    unsigned int getProgramPID();

    bool operator==(const ProgramAssociationSection &rhs) const;

    bool operator!=(const ProgramAssociationSection &rhs) const;

private:
    TSPayloadSections::ts_payload_header_fields headerFields{};
    unsigned short transport_stream_id;
    TSPayloadSections::ts_payload_version_section_fields versionSectionFields{};
    size_t numPasPrograms;
    pas_program *pasPrograms;

};


#endif //PROJECT_CODE_PROGRAMASSOCIATIONSECTION_H
