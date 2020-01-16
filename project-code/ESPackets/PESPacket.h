//
// Created by elnsa on 2019-12-29.
//

#ifndef PROJECT_CODE_PESPACKET_H
#define PROJECT_CODE_PESPACKET_H


#include <ostream>
#include "ESPacket.h"

/**
 * H.222.0 Table 2-17
 */

class PESPacket : public ESPacket {
public:

    ~PESPacket();
    /**
     *  H.222.0 Table 2-20 - enum for trick_mode_control_values
     */
    enum class trick_mode_control_values {
        fast_forward = 0b000,
        slow_motion = 0b001,
        freeze_frame = 0b010,
        fast_reverse = 0b011,
        slow_reverse = 0b100,
        reserved_control_values
    };

    /**
     * Convert the byte value for the trick_mode_control to the enum type
     *
     * @param x - byte value of the trick_mode_control
     * @return PESPacket::trick_mode_control_values - enum type
     */
    static PESPacket::trick_mode_control_values getType(unsigned long long x) {
        if (x == 0b000)
            return PESPacket::trick_mode_control_values::fast_forward;
        else if (x == 0b001)
            return PESPacket::trick_mode_control_values::slow_motion;
        else if (x == 0b010)
            return PESPacket::trick_mode_control_values::freeze_frame;
        else if (x == 0b011)
            return PESPacket::trick_mode_control_values::fast_reverse;
        else if (x == 0b100)
            return PESPacket::trick_mode_control_values::slow_reverse;
        else
            return PESPacket::trick_mode_control_values::reserved_control_values;
    }

    struct pts_dts_fields {
        unsigned long long PTS; //33-bit
        unsigned long long DTS; //33-bit
    };
    struct dsm_trick_mode_fields {
        PESPacket::trick_mode_control_values trick_mode_control; //3-bit
        unsigned char field_id; //2-bit
        unsigned char intra_slice_refresh; //1-bit
        unsigned char frequency_truncation; //2-bit
        unsigned char rep_cntrl; //5-bit
    };
    struct P_STD {
        ESPacket::start_code stream_id;
        unsigned char P_STD_buffer_bound_scale;
        unsigned short P_STD_buffer_size_bound;
    };
    struct system_header {
        unsigned short header_length;
        unsigned int rate_bound;
        unsigned char audio_bound;
        unsigned char fixed_flag;
        unsigned char CSPS_flag;
        unsigned char system_audio_lock_flag;
        unsigned char system_video_lock_flag;
        unsigned char video_bound;
        unsigned char packet_rate_restriction_flag;
        size_t numPSTD;
        PESPacket::P_STD *p_std;
    };
    struct pack_header {
        unsigned long long system_clock_reference;
        unsigned int program_mux_rate;
        PESPacket::system_header system_header{};
    };
    struct PES_extension_fields {
        unsigned char PES_private_data_flag; //1-bit
        unsigned char pack_header_field_flag; //1-bit
        unsigned char program_packet_sequence_counter_flag; //1-bit
        unsigned char P_STD_buffer_flag; //1-bit
        unsigned char PES_extension_flag_2; //1-bit
        unsigned char pack_field_length; //8-bit
        PESPacket::pack_header pack_header{};
        unsigned char program_packet_sequence_counter; //7-bit
        unsigned char MPEG1_MPEG2_identifier; //1-bit
        unsigned char original_stuff_length; //6-bit
        unsigned char P_STD_buffer_scale; //1-bit
        unsigned short P_STD_buffer_size; //13-bit
        unsigned char PES_extension_field_length; //7-bit
    };

    void print();

    PESPacket(start_code packet_type, unsigned char stream_id, unsigned short PES_packet_length,
              unsigned char PES_scrambling_control, unsigned char PES_priority, unsigned char data_alignment_indicator,
              unsigned char copyright, unsigned char original_or_copy, unsigned char PTS_DTS_flags,
              unsigned char ESCR_flag,
              unsigned char ES_rate_flag, unsigned char DSM_trick_mode_flag, unsigned char additional_copy_info_flag,
              unsigned char PES_CRC_flag, unsigned char PES_extension_flag, unsigned char PES_header_data_length,
              pts_dts_fields pts_dts, unsigned long long ESCR, unsigned int ES_rate,
              dsm_trick_mode_fields dsm_trick_mode,
              unsigned char additional_copy_info, unsigned short previous_PES_packet_CRC,
              PES_extension_fields pes_extension_fields, size_t data_length, unsigned char* data);

protected:

    /**
     * Fields listed as per H.222.0 Table 2-17
     */

    unsigned short PES_packet_length;
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
    pts_dts_fields pts_dts{};
    unsigned long long ESCR; //42-bit
    unsigned int ES_rate; //22-bit
    dsm_trick_mode_fields dsm_trick_mode{};
    unsigned char additional_copy_info; //7-bit
    unsigned short previous_PES_packet_CRC; //16-bit
    PES_extension_fields pes_extension_fields{};

    /**
     * data_length - indicates how many PES_Packet_data_bytes are read/found
     */
    size_t data_length;
    unsigned char *data;

};

#endif //PROJECT_CODE_PESPACKET_H
