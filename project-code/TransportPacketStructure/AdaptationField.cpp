//
// Created by bhave on 11/19/2019.
//

#include <iostream>
#include "AdaptationField.h"


void AdaptationField::print() {
    if (adaptation_field_length > 0) {
        printf(
                "AdaptationField:\nafl: %hhx, di: %hhx, rai: %hhx, espi: %hhx, pcrf: %hhx, opcrf: %hhx, spf: %hhx, tpdf: %hhx, afef: %hhx, pcr: %llx,\n opcr: %llx, sc: %hhx, tpdl: %hhx, afel: %hhx, ltwf: %hhx, prf: %hhx, ssf: %hhx, ltwvf: %hhx,\n ltwo: %hx, pr: %x, st: %hhx, DTSAU: %llx \n \n",
                adaptation_field_length, discontinuity_indicator, random_access_indicator,
                elementary_stream_priority_indicator, PCR_flag, OPCR_flag, splicing_point_flag,
                transport_private_data_flag, adaptation_field_extension_flag, program_clock_reference,
                original_program_clock_reference, splice_countdown, transport_private_data_length,
                adaptation_field_extension_length, ltw_flag, piecewise_rate_flag, seamless_splice_flag,
                ltw_valid_flag, ltw_offset, piecewise_rate, splice_type, DTS_next_AU);
    }
}

bool AdaptationField::operator==(const AdaptationField &rhs) const {
    return adaptation_field_length == rhs.adaptation_field_length &&
           discontinuity_indicator == rhs.discontinuity_indicator &&
           random_access_indicator == rhs.random_access_indicator &&
           elementary_stream_priority_indicator == rhs.elementary_stream_priority_indicator &&
           PCR_flag == rhs.PCR_flag &&
           OPCR_flag == rhs.OPCR_flag &&
           splicing_point_flag == rhs.splicing_point_flag &&
           transport_private_data_flag == rhs.transport_private_data_flag &&
           adaptation_field_extension_flag == rhs.adaptation_field_extension_flag &&
           program_clock_reference == rhs.program_clock_reference &&
           original_program_clock_reference == rhs.original_program_clock_reference &&
           splice_countdown == rhs.splice_countdown &&
           transport_private_data_length == rhs.transport_private_data_length &&
           adaptation_field_extension_length == rhs.adaptation_field_extension_length &&
           ltw_flag == rhs.ltw_flag &&
           piecewise_rate_flag == rhs.piecewise_rate_flag &&
           seamless_splice_flag == rhs.seamless_splice_flag &&
           ltw_valid_flag == rhs.ltw_valid_flag &&
           ltw_offset == rhs.ltw_offset &&
           piecewise_rate == rhs.piecewise_rate &&
           splice_type == rhs.splice_type &&
           DTS_next_AU == rhs.DTS_next_AU;
}

bool AdaptationField::operator!=(const AdaptationField &rhs) const {
    return !(rhs == *this);
}

AdaptationField::AdaptationField(AdaptationField::initializerStruct init) {

    this->adaptation_field_length = init.adaptation_field_length;
    this->discontinuity_indicator = init.discontinuity_indicator;
    this->random_access_indicator = init.random_access_indicator;
    this->elementary_stream_priority_indicator = init.elementary_stream_priority_indicator;
    this->PCR_flag = init.PCR_flag;
    this->OPCR_flag = init.OPCR_flag;
    this->splicing_point_flag = init.splicing_point_flag;
    this->transport_private_data_flag = init.transport_private_data_flag;
    this->adaptation_field_extension_flag = init.adaptation_field_extension_flag;
    this->program_clock_reference = init.program_clock_reference;
    this->original_program_clock_reference = init.original_program_clock_reference;
    this->splice_countdown = init.splice_countdown;
    this->transport_private_data_length = init.transport_private_data_length; // transport_private_data is not handled
    this->adaptation_field_extension_length = init.adaptation_field_extension_length;
    this->ltw_flag = init.ltw_flag;
    this->piecewise_rate_flag = init.piecewise_rate_flag;
    this->seamless_splice_flag = init.seamless_splice_flag;
    this->ltw_valid_flag = init.ltw_valid_flag;
    this->ltw_offset = init.ltw_offset;
    this->piecewise_rate = init.piecewise_rate;
    this->splice_type = init.splice_type;
    this->DTS_next_AU = init.DTS_next_AU;
}

unsigned char AdaptationField::getAdaptationFieldLength() const {
    return adaptation_field_length;
}
