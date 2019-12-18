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
     * @return unsigned char * TODO - change to size_t
     */
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
                long long pcr_base = BitManipulator::ReadNBits(&packet[index], 33);
                index += 3;
                long long pcr_ext = BitManipulator::ReadNBitsOffset(&packet[index], 7, 9);
                index += 2;
                out.program_clock_reference = (pcr_base * 300 + pcr_ext) & 0x3FFFFFFFFFF; //cast to a 42-bit field
            }
            if (out.OPCR_flag == 1) {
                long long opcr_base = BitManipulator::ReadNBits(&packet[index], 33);
                index += 3;
                long long opcr_ext = BitManipulator::ReadNBitsOffset(&packet[index], 7, 9);
                index += 2;
                out.original_program_clock_reference = (opcr_base * 300 + opcr_ext) & 0x3FFFFFFFFFF;
                //cast to a 42-bit field
            }
            if (out.splicing_point_flag == 1) {
                out.splice_countdown = packet[index];
                index++;
            }
            if (out.transport_private_data_flag == 1) {
                out.transport_private_data_length = packet[index];
                index++;
                index += out.transport_private_data_length;
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
                    out.splice_type = BitManipulator::ReadNBits(&packet[index], 4);
                    long long DTS_next_AU_32_30 = BitManipulator::ReadNBitsOffset(&packet[index], 4, 3);
                    index++;
                    long long DTS_next_AU_29_15 = BitManipulator::ReadNBits(&packet[index], 15);
                    index += 2;
                    long long DTS_next_AU_14_0 = BitManipulator::ReadNBits(&packet[index], 15);
                    index += 2;
                    out.DTS_next_AU = (DTS_next_AU_32_30 << 30) + (DTS_next_AU_29_15 << 15) + DTS_next_AU_14_0;
                }
                // TODO: This is where final reserved bytes would be handled.
            }
        }
        // TODO - what is this referring to???
        // +1 for adaptation_field_length see H.222 2.4.3.5


        //Todo - Change to Overriding standard library printf


        std::printf(
                "AdaptationField:\nafl: %hhx, di: %hhx, rai: %hhx, espi: %hhx, pcrf: %hhx, opcrf: %hhx, spf: %hhx, tpdf: %hhx, afef: %hhx, pcr: %llx,\n opcr: %llx, sc: %hhx, tpdl: %hhx, afel: %hhx, ltwf: %hhx, prf: %hhx, ssf: %hhx, ltwvf: %hhx,\n ltwo: %hx, pr: %x, st: %hhx, DTSAU: %llx \n \n",
                out.adaptation_field_length, out.discontinuity_indicator, out.random_access_indicator,
                out.elementary_stream_priority_indicator, out.PCR_flag, out.OPCR_flag, out.splicing_point_flag,
                out.transport_private_data_flag, out.adaptation_field_extension_flag, out.program_clock_reference,
                out.original_program_clock_reference, out.splice_countdown, out.transport_private_data_length,
                out.adaptation_field_extension_length, out.ltw_flag, out.piecewise_rate_flag, out.seamless_splice_flag,
                out.ltw_valid_flag, out.ltw_offset, out.piecewise_rate, out.splice_type, out.DTS_next_AU);
        return packet + 1 + out.adaptation_field_length;
    }
};