//
// Created by elnsa on 2020-01-05.
//

#ifndef PROJECT_CODE_PROGRAMMAPSECTION_H
#define PROJECT_CODE_PROGRAMMAPSECTION_H

#include "TSPayloadSections.h"

class ProgramMapSection {
public:
    /**
     * H.222.0, Table 2-29 - Stream type assignments
     */
    enum class StreamType {
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
    };

    static StreamType getStreamType(unsigned char stream_type) {
        switch (stream_type) {
            case 0x00:
                return StreamType::itu_iso_reserved;
            case 0x01:
                return StreamType::video_11172_2;
            case 0x02:
                return StreamType::video_H_262;
            case 0x03:
                return StreamType::audio_11172_3;
            case 0x04:
                return StreamType::audio_13818_3;
            case 0x05:
                return StreamType::private_section;
            case 0x06:
                return StreamType::PES_packet_private_data;
            case 0x07:
                return StreamType::mheg;
            case 0x08:
                return StreamType::dsm_cc;
            case 0x09:
                return StreamType::h_222_1;
            case 0x0A:
                return StreamType::type_A_13818_6;
            case 0x0B:
                return StreamType::type_B_13818_6;
            case 0x0C:
                return StreamType::type_C_13818_6;
            case 0x0D:
                return StreamType::type_D_13818_6;
            case 0x0E:
                return StreamType::auxillary_13818_1;
            default:
                if (0x0F <= stream_type <= 0x7F) {
                    return StreamType::reserved_13818_1;
                }
        }
        return StreamType::user_private;
    }

    struct program_element {
        unsigned char stream_type_value;
        StreamType stream_type;
        unsigned short elementary_PID;
        unsigned short ES_info_length;
    };

protected:
    /**
     * ProgramMapSection Fields
     */
    TSPayloadSections::ts_payload_header_fields headerFields;
    unsigned short program_number;
    TSPayloadSections::ts_payload_version_section_fields versionSectionFields;
    unsigned short PCR_PID;
    unsigned short program_info_length;
    program_element video_stream_element; //This decoder discards all elements that don't have stream_type video

public:
    ProgramMapSection(TSPayloadSections::ts_payload_header_fields hfs, unsigned short prognum,
                      TSPayloadSections::ts_payload_version_section_fields vsf, unsigned short pcrpid,
                      unsigned short pi_length, program_element progel);

    void print();

    unsigned int getVideoStreamPID();

    bool operator==(const ProgramMapSection &rhs) const;

    bool operator!=(const ProgramMapSection &rhs) const;
};


#endif //PROJECT_CODE_PROGRAMMAPSECTION_H
