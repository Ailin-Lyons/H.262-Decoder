//
// Created by elnsa on 2019-12-29.
//

#ifndef PROJECT_CODE_PESPACKET_H
#define PROJECT_CODE_PESPACKET_H


#include "ESPacket.h"

class PESPacket : public ESPacket {
public:
    struct pts_dts_fields {
        unsigned long long PTS; //30-bit
        unsigned long long DTS; //30-bit
    };
    struct dsm_trick_mode_fields {
        unsigned char trick_mode_control; //3-bit
        unsigned char field_id; //2-bit
        unsigned char intra_slice_refresh; //1-bit
        unsigned char frequency_truncation; //2-bit
        unsigned char rep_cntrl; //5-bit
    };
    struct PES_extension_fields {
        unsigned char PES_private_data_flag; //1-bit
        unsigned char pack_header_field_flag; //1-bit
        unsigned char program_packet_sequence_counter_flag; //1-bit
        unsigned char P_STD_buffer_flag; //1-bit
        unsigned char PES_extension_flag_2; //1-bit
        unsigned char pack_field_length; //8-bit
        //PESPacket::PackHeader pack_header; //TODO make a struct
        unsigned char program_packet_sequence_counter; //7-bit
        unsigned char MPEG1_MPEG2_identifier; //1-bit
        unsigned char original_stuff_length; //6-bit
        unsigned char P_STD_buffer_scale; //1-bit
        unsigned short P_STD_buffer_size; //13-bit
        unsigned char PES_extension_field_length; //7-bit
    };


protected:
    unsigned char PES_scrambling_control; //2-bit
    unsigned char PES_priority; //1-bit
    unsigned char data_alignment_indicator; //1-bit
    unsigned char copyright; //1-bit
    unsigned char original_or_copy; //1-bit
    unsigned char PTS_DTS_flags; //2-bit
    unsigned char ESCR_flag; //1-bit
    unsigned char ES_rate_flag; //1-bit
    unsigned char DSM_trick_mode_flag; //1-bit
    unsigned char additional_copy_info_flag; //1-bit
    unsigned char PES_CRC_flag; //1-bit
    unsigned char PES_extension_flag; //1-bit
    unsigned char PES_header_data_length; //8-bit
    pts_dts_fields pts_dts;
    unsigned long long ESCR; //42-bit
    unsigned int ES_rate; //22-bit
    dsm_trick_mode_fields dsm_trick_mode;
    unsigned char additional_copy_info; //7-bit
    unsigned short previous_PES_packet_CRC; //16-bit

    unsigned int data_length; //TODO how to handle elementary stream packets: state machine or children?
    unsigned char *data;

};

#endif //PROJECT_CODE_PESPACKET_H
