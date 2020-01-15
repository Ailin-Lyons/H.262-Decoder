//
// Created by bhave on 11/19/2019.
//

#ifndef PROJECT_CODE_ADAPTATIONFIELD_H
#define PROJECT_CODE_ADAPTATIONFIELD_H


class AdaptationField {

public:

    /**
     * enum class for different splice decoding delays
     */
    enum class ST {
        splice_decoding_delay_other,
        splice_decoding_delay_120,
        splice_decoding_delay_150,
        splice_decoding_delay_225,
        splice_decoding_delay_250
    };

    /**
     * struct used for initializing  an instance of AdaptationField
     */

    struct initializerStruct {
        unsigned char adaptation_field_length;
        unsigned char discontinuity_indicator;
        unsigned char random_access_indicator;
        unsigned char elementary_stream_priority_indicator;
        unsigned char PCR_flag;
        unsigned char OPCR_flag;
        unsigned char splicing_point_flag;
        unsigned char transport_private_data_flag;
        unsigned char adaptation_field_extension_flag;
        unsigned long long program_clock_reference;
        unsigned long long original_program_clock_reference;
        unsigned char splice_countdown;
        unsigned char transport_private_data_length; // transport_private_data is not handled
        unsigned char adaptation_field_extension_length;
        unsigned char ltw_flag;
        unsigned char piecewise_rate_flag;
        unsigned char seamless_splice_flag;
        unsigned char ltw_valid_flag;
        unsigned short ltw_offset;
        unsigned int piecewise_rate;
        ST splice_type;
        unsigned long long DTS_next_AU = 0;
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


private:
    /**
     * The AdaptationField header fields in order. See H222.0 Table 2-6
     */

    unsigned char adaptation_field_length;
    unsigned char discontinuity_indicator;
    unsigned char random_access_indicator;
    unsigned char elementary_stream_priority_indicator;
    unsigned char PCR_flag;
    unsigned char OPCR_flag;
    unsigned char splicing_point_flag;
    unsigned char transport_private_data_flag;
    unsigned char adaptation_field_extension_flag;
    unsigned long long program_clock_reference;
    unsigned long long original_program_clock_reference;
    unsigned char splice_countdown;
    unsigned char transport_private_data_length; // transport_private_data is not handled
    unsigned char adaptation_field_extension_length;
    unsigned char ltw_flag;
    unsigned char piecewise_rate_flag;
    unsigned char seamless_splice_flag;
    unsigned char ltw_valid_flag;
    unsigned short ltw_offset;
    unsigned int piecewise_rate;
    ST splice_type;
    unsigned long long DTS_next_AU;

public:

    void print();
    AdaptationField(initializerStruct init);
    ~AdaptationField() = default;

    bool operator==(const AdaptationField &rhs) const;

    unsigned char getAdaptationFieldLength() const;

    bool operator!=(const AdaptationField &rhs) const;
};


#endif //PROJECT_CODE_ADAPTATIONFIELD_H
