//
// Created by bhave on 11/19/2019.
//

#include <iostream>
#include "AdaptationField.h"

AdaptationField::AdaptationField() {

}

AdaptationField::~AdaptationField() {
        // TODO free private_data_byte if malloc'd
}

void AdaptationField::toString() {
    std::printf(
            "AdaptationField:\nafl: %hhx, di: %hhx, rai: %hhx, espi: %hhx, pcrf: %hhx, opcrf: %hhx, spf: %hhx, tpdf: %hhx, afef: %hhx, pcr: %llx,\n opcr: %llx, sc: %hhx, tpdl: %hhx, afel: %hhx, ltwf: %hhx, prf: %hhx, ssf: %hhx, ltwvf: %hhx,\n ltwo: %hx, pr: %x, st: %hhx, DTSAU: %llx \n \n",
            adaptation_field_length, discontinuity_indicator, random_access_indicator,
            elementary_stream_priority_indicator, PCR_flag, OPCR_flag, splicing_point_flag,
            transport_private_data_flag, adaptation_field_extension_flag, program_clock_reference,
            original_program_clock_reference, splice_countdown, transport_private_data_length,
            adaptation_field_extension_length, ltw_flag, piecewise_rate_flag, seamless_splice_flag,
            ltw_valid_flag, ltw_offset, piecewise_rate, splice_type, DTS_next_AU);
}
