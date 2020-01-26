//
// Created by elnsa on 2019-11-20.
//

#include "../../Util/BitManipulator.cpp"
#include "../../StreamPackets/TSPackets/AdaptationField.h"

class AFParser {
public:
    /**
     * Builds an instance of AdaptationField from a TS Packet.
     * @param packet - pointer to position in TS from which to start reading
     * @return an instance AdaptationField
     */
    static AdaptationField generateAdaptationField(unsigned char *packet) {
        AdaptationField::initializerStruct af{};
        int index = 0;
        af.adaptation_field_length = packet[index];
        index++;
        if (af.adaptation_field_length > 0) {
            af.discontinuity_indicator = BitManipulator::readNBits(&packet[index], 1);
            af.random_access_indicator = BitManipulator::readNBitsOffset(&packet[index], 1, 1);
            af.elementary_stream_priority_indicator = BitManipulator::readNBitsOffset(&packet[index], 2, 1);
            af.PCR_flag = BitManipulator::readNBitsOffset(&packet[index], 3, 1);
            af.OPCR_flag = BitManipulator::readNBitsOffset(&packet[index], 4, 1);
            af.splicing_point_flag = BitManipulator::readNBitsOffset(&packet[index], 5, 1);
            af.transport_private_data_flag = BitManipulator::readNBitsOffset(&packet[index], 6, 1);
            af.adaptation_field_extension_flag = BitManipulator::readNBitsOffset(&packet[index], 7, 1);
            index++;
            if (af.PCR_flag == 1) {
                unsigned long long pcr_base = BitManipulator::readNBits(&packet[index], 33);
                index += 4;
                unsigned long long pcr_ext = BitManipulator::readNBitsOffset(&packet[index], 7, 9);
                index += 2;
                af.program_clock_reference =
                        (pcr_base * 300 + pcr_ext) & 0x3FFFFFFFFFF; //cast to a 42-bit field
            }
            if (af.OPCR_flag == 1) {
                unsigned long long opcr_base = BitManipulator::readNBits(&packet[index], 33);
                index += 4;
                unsigned long long opcr_ext = BitManipulator::readNBitsOffset(&packet[index], 7, 9);
                index += 2;
                af.original_program_clock_reference =
                        (opcr_base * 300 + opcr_ext) & 0x3FFFFFFFFFF; //cast to a 42-bit field
            }
            if (af.splicing_point_flag == 1) {
                af.splice_countdown = packet[index];
                index++;
            }
            if (af.transport_private_data_flag == 1) {
                af.transport_private_data_length = packet[index];
                index++;
                index += af.transport_private_data_length;
            }
            if (af.adaptation_field_extension_flag == 1) {
                af.adaptation_field_extension_length = packet[index];
                index++;
                af.ltw_flag = BitManipulator::readNBits(&packet[index], 1);
                af.piecewise_rate_flag = BitManipulator::readNBitsOffset(&packet[index], 1, 1);
                af.seamless_splice_flag = BitManipulator::readNBitsOffset(&packet[index], 2, 1);
                index++;
                if (af.ltw_flag == 1) {
                    af.ltw_valid_flag = BitManipulator::readNBits(&packet[index], 1);
                    af.ltw_offset = BitManipulator::readNBitsOffset(&packet[index], 1, 15);
                    index += 2;
                }
                if (af.piecewise_rate_flag == 1) {
                    af.piecewise_rate = BitManipulator::readNBitsOffset(&packet[index], 2, 22);
                    index += 3;
                }
                if (af.seamless_splice_flag == 1) {
                    af.splice_type = AdaptationField::getSpliceType(BitManipulator::readNBits(&packet[index], 4));
                    unsigned long long DTS_next_AU_32_30 = BitManipulator::readNBitsOffset(&packet[index], 4, 3);
                    index++;
                    unsigned long long DTS_next_AU_29_15 = BitManipulator::readNBits(&packet[index], 15);
                    index += 2;
                    unsigned long long DTS_next_AU_14_0 = BitManipulator::readNBits(&packet[index], 15);
                    af.DTS_next_AU =
                            (DTS_next_AU_32_30 << 30) + (DTS_next_AU_29_15 << 15) + DTS_next_AU_14_0;
                }
            }
        }
        return AdaptationField(af);
    }
};
