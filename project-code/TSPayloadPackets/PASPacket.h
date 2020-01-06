//
// Created by elnsa on 2020-01-05.
//

#ifndef PROJECT_CODE_PASPACKET_H
#define PROJECT_CODE_PASPACKET_H


#include "TSPayloadPacket.h"

class PASPacket {
    struct pas_program {
        unsigned short program_number; //16-bit
        unsigned short assosciated_pid; // 13-bit this holds either network_PID if program_number==0 else program_map_PID
    };
    TSPayloadPacket::ts_payload_header_fields headerFields;
    unsigned short transport_stream_id;
    TSPayloadPacket::ts_payload_version_section_fields versionSectionFields;
    unsigned int numPasPrograms;
    pas_program* pasProgram;
};


#endif //PROJECT_CODE_PASPACKET_H
