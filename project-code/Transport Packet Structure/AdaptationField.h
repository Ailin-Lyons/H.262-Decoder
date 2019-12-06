//
// Created by bhave on 11/19/2019.
//

#ifndef PROJECT_CODE_ADAPTATIONFIELD_H
#define PROJECT_CODE_ADAPTATIONFIELD_H


class AdaptationField {

public:

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
    unsigned char splice_type; //TODO make splice_type an enum?
    unsigned long long DTS_next_AU;

public:

    AdaptationField();
    ~AdaptationField();
};


#endif //PROJECT_CODE_ADAPTATIONFIELD_H
