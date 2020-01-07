//
// Created by elnsa on 2020-01-05.
//

#ifndef PROJECT_CODE_PMSPACKET_H
#define PROJECT_CODE_PMSPACKET_H

#include "TSPayloadPacket.h"

class PMSPacket {
    /**
     * H.222.0, Table 2-29 - Stream type assignments
     */
    enum class stream_type{
        itu_iso_reserved,
        video_11172_2,
        video_H_262,
        audio_11172_3,
        audio_13818_3,
        private_section,
        PES_packet_private_data,
        mheg,
        dsm_cc,
        h_222_1,
        type_A_13818_6,
        type_B_13818_6,
        type_C_13818_6,
        type_D_13818_6,
        auxillary_13818_1,
        reserved_13818_1,
        user_private
    };//TODO static assign class

    struct program_element{
        stream_type stream_type;
        unsigned short elementary_PID;
        unsigned short ES_info_length;
        unsigned int numDescriptors;
        //descriptor* descriptors; // TODO make descriptor classes
    };
    TSPayloadPacket::ts_payload_header_fields headerFields;
    unsigned short program_number;
    TSPayloadPacket::ts_payload_version_section_fields versionSectionFields;
    unsigned short PCR_PID;
    unsigned short program_info_length;
    unsigned char* program_info;
    unsigned int numDescriptors;
    //descriptor* descriptors; // TODO make descriptor classes
};


#endif //PROJECT_CODE_PMSPACKET_H
