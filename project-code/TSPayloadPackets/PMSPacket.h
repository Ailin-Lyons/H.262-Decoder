//
// Created by elnsa on 2020-01-05.
//

#ifndef PROJECT_CODE_PMSPACKET_H
#define PROJECT_CODE_PMSPACKET_H


class PMSPacket {
    TSPayloadPacket::ts_payload_header_fields headerFields;
    unsigned short program_number;
    TSPayloadPacket::ts_payload_version_section_fields versionSectionFields;
    unsigned short PCR_PID;
    unsigned short program_info_length;
    unsigned char* program_info;
    // TODO continue here
};


#endif //PROJECT_CODE_PMSPACKET_H
