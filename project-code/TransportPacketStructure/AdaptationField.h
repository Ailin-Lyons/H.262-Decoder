//
// Created by bhave on 11/19/2019.
//

#ifndef PROJECT_CODE_ADAPTATIONFIELD_H
#define PROJECT_CODE_ADAPTATIONFIELD_H


class AdaptationField {

public:

    enum class ST {
        splice_decoding_delay_120,
        splice_decoding_delay_150,
        splice_decoding_delay_225,
        splice_decoding_delay_250,
        splice_decoding_delay_other
    };

    /**
 * Returns the correct PID given parsed_pid
 *
 * @param parsed_pid
 * @return PID
 */

    static ST getSpliceType(unsigned char splice_type) {
        if (splice_type == 0x0) {
            return ST::splice_decoding_delay_120;
        } else if (splice_type == 0x1) {
            return ST::splice_decoding_delay_150;
        } else if (splice_type == 0x2) {
            return ST::splice_decoding_delay_225;
        } else if (splice_type == 0x3) {
            return ST::splice_decoding_delay_250;
        } else {
            return ST::splice_decoding_delay_other;
        }
    }

    /**
     * The AdaptationField header fields in order. See H222.0 Table 2-6
     */

    unsigned char adaptation_field_length = 0;
    unsigned char discontinuity_indicator = 0;
    unsigned char random_access_indicator = 0;
    unsigned char elementary_stream_priority_indicator = 0;
    unsigned char PCR_flag = 0;
    unsigned char OPCR_flag = 0;
    unsigned char splicing_point_flag = 0;
    unsigned char transport_private_data_flag = 0;
    unsigned char adaptation_field_extension_flag = 0;
    unsigned long long program_clock_reference = 0;
    unsigned long long original_program_clock_reference = 0;
    unsigned char splice_countdown = 0;
    unsigned char transport_private_data_length = 0; // transport_private_data is not handled
    unsigned char adaptation_field_extension_length = 0;
    unsigned char ltw_flag = 0;
    unsigned char piecewise_rate_flag = 0;
    unsigned char seamless_splice_flag = 0;
    unsigned char ltw_valid_flag = 0;
    unsigned short ltw_offset = 0;
    unsigned int piecewise_rate = 0;
    ST splice_type = ST::splice_decoding_delay_other;
    unsigned long long DTS_next_AU = 0;

public:

    void toString();
    AdaptationField();
    ~AdaptationField();
};


#endif //PROJECT_CODE_ADAPTATIONFIELD_H
