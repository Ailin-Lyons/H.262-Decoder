//
// Created by elnsa on 2019-12-29.
//

#include "PESPacket.h"


void PESPacket::print() {
    //TODO
}

PESPacket::PESPacket(start_code packet_type, unsigned char stream_id, unsigned short PES_packet_length,
                    unsigned char PES_scrambling_control, unsigned char PES_priority, unsigned char data_alignment_indicator, unsigned char copyright, unsigned char original_or_copy,
                     unsigned char PTS_DTS_flags, unsigned char ESCR_flag, unsigned char ES_rate_flag,
                     unsigned char DSM_trick_mode_flag, unsigned char additional_copy_info_flag,
                     unsigned char PES_CRC_flag, unsigned char PES_extension_flag, unsigned char PES_header_data_length,
                     PESPacket::pts_dts_fields pts_dts, unsigned long long ESCR, unsigned int ES_rate,
                     PESPacket::dsm_trick_mode_fields dsm_trick_mode, unsigned char additional_copy_info,
                     unsigned short previous_PES_packet_CRC, PESPacket::PES_extension_fields pes_extension_fields) {
    this->packet_type = packet_type;
    this->stream_id = stream_id;
    this->PES_packet_length = PES_packet_length;
    this->PES_scrambling_control = PES_scrambling_control;
    this->PES_priority = PES_priority;
    this->data_alignment_indicator = data_alignment_indicator;
    this->copyright = copyright;
    this->original_or_copy = original_or_copy;
    this->PTS_DTS_flags = PTS_DTS_flags;
    this->ESCR_flag = ESCR_flag;
    this->ES_rate_flag = ES_rate_flag;
    this->DSM_trick_mode_flag = DSM_trick_mode_flag;
    this->additional_copy_info_flag = additional_copy_info_flag;
    this->PES_CRC_flag = PES_CRC_flag;
    this->PES_extension_flag = PES_extension_flag;
    this->PES_header_data_length = PES_header_data_length;
    this->pts_dts = pts_dts;
    this->ESCR = ESCR;
    this->ES_rate = ES_rate;
    this->dsm_trick_mode = dsm_trick_mode;
    this->additional_copy_info = additional_copy_info;
    this->previous_PES_packet_CRC = previous_PES_packet_CRC;
    this->pes_extension_fields = pes_extension_fields;
}
