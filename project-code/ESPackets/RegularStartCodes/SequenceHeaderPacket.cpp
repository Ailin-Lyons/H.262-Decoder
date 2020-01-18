//
// Created by elnsa on 2019-12-29.
//

#include "SequenceHeaderPacket.h"

SequenceHeaderPacket::SequenceHeaderPacket(SequenceHeaderPacket::initializerStruct init) {
    packet_type = ESPacket::start_code::sequence_header;
    stream_id = 0xB3;
    horizontal_size_value = init.horizontal_size_value;
    vertical_size_value = init.vertical_size_value;
    aspect_ratio_information = init.aspect_ratio_information;
    frame_rate_code = init.frame_rate_code;
    bit_rate_value = init.bit_rate_value;
    vbv_buffer_size_value = init.vbv_buffer_size_value;
    constrained_parameters_flag = init.constrained_parameters_flag;
    load_intra_quantiser_matrix = init.load_intra_quantiser_matrix;
    intra_quantiser_matrix = init.intra_quantiser_matrix;
    load_non_intra_quantiser_matrix = init.load_non_intra_quantiser_matrix;
    non_intra_quantiser_matrix = init.non_intra_quantiser_matrix;
}

void SequenceHeaderPacket::print() {
    printf(
            "SequenceHeaderPacket: hsv %x, vsv %x, ari %x, frc %x, brv %x, vbv_buf %x, cpf %x, liqm %x, iqm %x, lniqm %x, niqm %x.\n",
            horizontal_size_value, vertical_size_value, aspect_ratio_information, frame_rate_code,
            bit_rate_value, vbv_buffer_size_value, constrained_parameters_flag, load_intra_quantiser_matrix,
            intra_quantiser_matrix, load_non_intra_quantiser_matrix, non_intra_quantiser_matrix);
}

bool SequenceHeaderPacket::operator==(const SequenceHeaderPacket &rhs) const {
    bool eq = horizontal_size_value == rhs.horizontal_size_value &&
              vertical_size_value == rhs.vertical_size_value &&
              aspect_ratio_information == rhs.aspect_ratio_information &&
              frame_rate_code == rhs.frame_rate_code &&
              bit_rate_value == rhs.bit_rate_value &&
              vbv_buffer_size_value == rhs.vbv_buffer_size_value &&
              constrained_parameters_flag == rhs.constrained_parameters_flag &&
              load_intra_quantiser_matrix == rhs.load_intra_quantiser_matrix &&
              load_non_intra_quantiser_matrix == rhs.load_non_intra_quantiser_matrix;
    if (!eq) return eq;
    if (load_intra_quantiser_matrix) {
        for (int i = 0; i < 64; i++) {
            if (intra_quantiser_matrix[i] != rhs.intra_quantiser_matrix[i]) return false;
        }
    }
    if (load_non_intra_quantiser_matrix) {
        for (int i = 0; i < 64; i++) {
            if (non_intra_quantiser_matrix[i] != rhs.non_intra_quantiser_matrix[i]) return false;
        }
    }
    return true;
}

bool SequenceHeaderPacket::operator!=(const SequenceHeaderPacket &rhs) const {
    return !(rhs == *this);
}

SequenceHeaderPacket::~SequenceHeaderPacket() {
    if (load_intra_quantiser_matrix) {
        free(intra_quantiser_matrix);
    }
    if (load_non_intra_quantiser_matrix) {
        free(non_intra_quantiser_matrix);
    }
}

unsigned short SequenceHeaderPacket::getHVal() const {
    return horizontal_size_value;
}

unsigned short SequenceHeaderPacket::getVVal() const {
    return vertical_size_value;
}

unsigned char SequenceHeaderPacket::getAspectRatioInformation() const {
    return aspect_ratio_information;
}

unsigned char SequenceHeaderPacket::getFrameRate() const {
    return frame_rate_code;
}

unsigned int SequenceHeaderPacket::getBitRateVal() {
    return bit_rate_value;
}

unsigned int SequenceHeaderPacket::getVBVBufVal() {
    return (unsigned int) vbv_buffer_size_value;
}

const bool SequenceHeaderPacket::getCPFlag() {
    return constrained_parameters_flag;
}
