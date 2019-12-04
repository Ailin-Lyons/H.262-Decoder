//
// Created by elnsa on 2019-11-20.
//

#include "../Util/BitManipulator.cpp"
#include "../Transport Packet Structure/AdaptationField.h"

class AFParser {

public:
    static unsigned char *generateAdaptationField(unsigned char *packet, AdaptationField *adaptation_field) {
        AdaptationField out = AdaptationField();
        out.adaptation_field_length = packet[0];
        if (out.adaptation_field_length > 0) {
            out.discontinuity_indicator = (packet[1] >> 7) & 0x1;
            out.random_access_indicator = (packet[1] >> 6) & 0x1;
            out.elementary_stream_priority_indicator = (packet[1] >> 5) & 0x1;
            out.PCR_flag = (packet[1] >> 4) & 0x1;
            out.OPCR_flag = (packet[1] >> 3) & 0x1;
            out.splicing_point_flag = (packet[1] >> 2) & 0x1;
            out.transport_private_data_flag = (packet[1] >> 1) & 0x1;
            out.adaptation_field_extension_flag = packet[1] & 0x1;
            if (out.PCR_flag == 1) {
                out.program_clock_reference_base = BitManipulator::ReadNBits(&packet[2], 33);
                out.program_clock_reference_extension = BitManipulator::ReadNBitsOffset(&packet[5], 7, 9);
            }
            if (out.OPCR_flag == 1) {
                // TODO
            }
            if (out.splicing_point_flag == 1) {

            }
            if (out.transport_private_data_flag == 1) {

            }
        }


        return packet + out.adaptation_field_length; // TODO
    }
};