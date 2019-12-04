//
// Created by elnsa on 2019-11-20.
//

#include <cstdlib>
#include "../Util/BitManipulator.cpp"
#include "../Transport Packet Structure/AdaptationField.h"

class AFParser {

public:
    static unsigned char *generateAdaptationField(unsigned char *packet, AdaptationField *adaptation_field) {
        AdaptationField out = AdaptationField();
        int index = 0;
        out.adaptation_field_length = packet[index];
        index++;
        if (out.adaptation_field_length > 0) {
            out.discontinuity_indicator = BitManipulator::ReadNBits(&packet[index], 1);
            out.random_access_indicator = BitManipulator::ReadNBitsOffset(&packet[index], 1, 1);
            out.elementary_stream_priority_indicator = BitManipulator::ReadNBitsOffset(&packet[index], 2, 1);
            out.PCR_flag = BitManipulator::ReadNBitsOffset(&packet[index], 3, 1);
            out.OPCR_flag = BitManipulator::ReadNBitsOffset(&packet[index], 4, 1);
            out.splicing_point_flag = BitManipulator::ReadNBitsOffset(&packet[index], 5, 1);
            out.transport_private_data_flag = BitManipulator::ReadNBitsOffset(&packet[index], 6, 1);
            out.adaptation_field_extension_flag = BitManipulator::ReadNBitsOffset(&packet[index], 7, 1);
            index++;
            if (out.PCR_flag == 1) {
                out.program_clock_reference_base = BitManipulator::ReadNBits(&packet[index], 33); //TODO turn these into program_clock_reference_base
                index += 3;
                out.program_clock_reference_extension = BitManipulator::ReadNBitsOffset(&packet[index], 7, 9);
                index += 2;
            }
            if (out.OPCR_flag == 1) {
                out.original_program_clock_reference_base = BitManipulator::ReadNBits(&packet[index], 33); //TODO turn these into OPCR
                index += 3;
                out.original_program_clock_reference_extension = BitManipulator::ReadNBitsOffset(&packet[index], 7, 9);
                index += 2;
            }
            if (out.splicing_point_flag == 1) {
                out.splice_countdown = packet[index];
                index++;
            }
            if (out.transport_private_data_flag == 1) {
                out.transport_private_data_length = packet[index];
                index++;
                out.private_data_byte = (unsigned char *) malloc(sizeof(char) * out.transport_private_data_length); // TODO do we want to bother mallocing this? or just throw the field out.
                for (int i = 0; i < out.transport_private_data_length; i++) {
                    out.private_data_byte[i] = packet[index];
                    index++;
                }
            }
            if (out.adaptation_field_extension_flag == 1) {
                out.adaptation_field_extension_length = packet[index];
                int af_start = index;
                index++;
                out.ltw_flag = BitManipulator::ReadNBits(&packet[index], 1);
                out.piecewise_rate_flag = BitManipulator::ReadNBitsOffset(&packet[index], 1, 1);
                out.seamless_splice_flag = BitManipulator::ReadNBitsOffset(&packet[index], 2, 1);
                index++;
                if (out.ltw_flag == 1) {
                    out.ltw_valid_flag = BitManipulator::ReadNBits(&packet[index], 1);
                    out.ltw_offset = BitManipulator::ReadNBitsOffset(&packet[index], 1, 15);
                    index += 2;
                }
                if (out.piecewise_rate_flag == 1) {
                    out.ltw_offset = BitManipulator::ReadNBitsOffset(&packet[index], 2, 22);
                    index += 3;
                }
                if (out.seamless_splice_flag == 1) {
                    out.splice_type = BitManipulator::ReadNBits(&packet[index], 4); //TODO make enum?
                    out.DTS_next_AU_32_30 = BitManipulator::ReadNBitsOffset(&packet[index], 4, 3); //TODO turn these next fields into DTU_next_AU
                    //TODO deal with markerbit
                    index++;
                    out.DTS_next_AU_29_15 = BitManipulator::ReadNBits(&packet[index], 15);
                    // TODO deal with markerbit
                    index += 2;
                    out.DTS_next_AU_14_0 = BitManipulator::ReadNBits(&packet[index], 15);
                    // TODO deal with markerbit
                    index += 2;
                }
                // This is where final reserved bytes would be handled.
            }
        }
        return packet + 1 + out.adaptation_field_length;
    }
};