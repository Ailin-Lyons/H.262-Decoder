//
// Created by elnsa on 2019-11-20.
//

#include <cstdlib>
#include <cstdio>
#include "../Util/BitManipulator.cpp"
#include "../TransportPacketStructure/AdaptationField.h"

class AFParser {    // TODO test this class
public:
    /**
     *
     * @param packet - pointer to packet data
     * @param adaptation_field - TODO why do we need this?
     * @return unsigned size_t The number of bits taken up by this packet
     */
    static size_t generateAdaptationField(unsigned char *packet, AdaptationField *adaptation_field) {
        int index = 0;
        adaptation_field->adaptation_field_length = packet[index];
        index++;
        if (adaptation_field->adaptation_field_length > 0) {
            adaptation_field->discontinuity_indicator = BitManipulator::ReadNBits(&packet[index], 1);
            adaptation_field->random_access_indicator = BitManipulator::ReadNBitsOffset(&packet[index], 1, 1);
            adaptation_field->elementary_stream_priority_indicator = BitManipulator::ReadNBitsOffset(&packet[index], 2,
                                                                                                     1);
            adaptation_field->PCR_flag = BitManipulator::ReadNBitsOffset(&packet[index], 3, 1);
            adaptation_field->OPCR_flag = BitManipulator::ReadNBitsOffset(&packet[index], 4, 1);
            adaptation_field->splicing_point_flag = BitManipulator::ReadNBitsOffset(&packet[index], 5, 1);
            adaptation_field->transport_private_data_flag = BitManipulator::ReadNBitsOffset(&packet[index], 6, 1);
            adaptation_field->adaptation_field_extension_flag = BitManipulator::ReadNBitsOffset(&packet[index], 7, 1);
            index++;
            if (adaptation_field->PCR_flag == 1) {
                long long pcr_base = BitManipulator::ReadNBits(&packet[index], 33);
                index += 3;
                long long pcr_ext = BitManipulator::ReadNBitsOffset(&packet[index], 7, 9);
                index += 2;
                adaptation_field->program_clock_reference =
                        (pcr_base * 300 + pcr_ext) & 0x3FFFFFFFFFF; //cast to a 42-bit field
            }
            if (adaptation_field->OPCR_flag == 1) {
                long long opcr_base = BitManipulator::ReadNBits(&packet[index], 33);
                index += 3;
                long long opcr_ext = BitManipulator::ReadNBitsOffset(&packet[index], 7, 9);
                index += 2;
                adaptation_field->original_program_clock_reference =
                        (opcr_base * 300 + opcr_ext) & 0x3FFFFFFFFFF; //cast to a 42-bit field
            }
            if (adaptation_field->splicing_point_flag == 1) {
                adaptation_field->splice_countdown = packet[index];
                index++;
            }
            if (adaptation_field->transport_private_data_flag == 1) {
                adaptation_field->transport_private_data_length = packet[index];
                index++;
                index += adaptation_field->transport_private_data_length;
            }
            if (adaptation_field->adaptation_field_extension_flag == 1) {
                adaptation_field->adaptation_field_extension_length = packet[index];
                int af_start = index;
                index++;
                adaptation_field->ltw_flag = BitManipulator::ReadNBits(&packet[index], 1);
                adaptation_field->piecewise_rate_flag = BitManipulator::ReadNBitsOffset(&packet[index], 1, 1);
                adaptation_field->seamless_splice_flag = BitManipulator::ReadNBitsOffset(&packet[index], 2, 1);
                index++;
                if (adaptation_field->ltw_flag == 1) {
                    adaptation_field->ltw_valid_flag = BitManipulator::ReadNBits(&packet[index], 1);
                    adaptation_field->ltw_offset = BitManipulator::ReadNBitsOffset(&packet[index], 1, 15);
                    index += 2;
                }
                if (adaptation_field->piecewise_rate_flag == 1) {
                    adaptation_field->ltw_offset = BitManipulator::ReadNBitsOffset(&packet[index], 2, 22);
                    index += 3;
                }
                if (adaptation_field->seamless_splice_flag == 1) {
                    adaptation_field->splice_type = BitManipulator::ReadNBits(&packet[index], 4);
                    long long DTS_next_AU_32_30 = BitManipulator::ReadNBitsOffset(&packet[index], 4, 3);
                    index++;
                    long long DTS_next_AU_29_15 = BitManipulator::ReadNBits(&packet[index], 15);
                    index += 2;
                    long long DTS_next_AU_14_0 = BitManipulator::ReadNBits(&packet[index], 15);
                    adaptation_field->DTS_next_AU =
                            (DTS_next_AU_32_30 << 30) + (DTS_next_AU_29_15 << 15) + DTS_next_AU_14_0;
                }
            }
        }
        return adaptation_field->adaptation_field_length + 1; // +1 for adaptation_field_length see H.222 2.4.3.5
    }
};
