//
// Created by elnsa on 2020-01-16.
//

#include "SequenceDisplayExtensionPacket.h"

SequenceDisplayExtensionPacket::SequenceDisplayExtensionPacket(SequenceDisplayExtensionPacket::initializerStruct init) {
    packet_type = ESPacket::start_code::extension;
    stream_id = 0xB5;
    e_type = ExtensionPacket::extension_type::sequence_display;
    video_format = init.video_format;
    colour_description = init.colour_description;
    colour_primaries = init.colour_primaries;
    transfer_characteristics = init.transfer_characteristics;
    matrix_coefficients = init.matrix_coefficients;
    display_horizontal_size = init.display_horizontal_size;
    display_vertical_size = init.display_vertical_size;
}

void SequenceDisplayExtensionPacket::print() {
    printf(
            "SequenceDisplayExtensionPacket: vf %x, cd %x, cp %x, tc %x, matrix_coefficients %x, dhs %x, dvs %x\n",
            video_format, colour_description, colour_primaries, transfer_characteristics,
            matrix_coefficients, display_horizontal_size, display_vertical_size);
}

bool SequenceDisplayExtensionPacket::operator==(const SequenceDisplayExtensionPacket &rhs) const {
    return video_format == rhs.video_format && colour_description == rhs.colour_description &&
           colour_primaries == rhs.colour_primaries && transfer_characteristics == rhs.transfer_characteristics &&
           matrix_coefficients == rhs.matrix_coefficients && display_horizontal_size == rhs.display_horizontal_size &&
           display_vertical_size == rhs.display_vertical_size;
}

bool SequenceDisplayExtensionPacket::operator!=(const SequenceDisplayExtensionPacket &rhs) const {
    return !(rhs == *this);
}
