//
// Created by bhave on 1/4/2020.
//

#include "../ESParser.h"
#include "../../StreamPackets/ESPackets/PESPacket.h"

// TODO - convert macros to compilation flag based
// TODO - check to make sure that all the reserved, stuffing, marker bits are correctly skipped
//  @Bhavesh Dont worry about any stuffing bits at the end since ESParser::next_start_code() will skip them anyways
#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))
#define marker(x, y) (valueChecks((x), (y), __func__))
#define mark1 (valueChecks(1, 0b1, __func__))

class PESParser {
public:

    /**
     * Parses the next packet as a PESPacket if possible
     * @return PESPacket* - parsed packet
     * @throws PacketException - if packet is not a H.222.0 video stream packet : stream_id/start_code = E0-EF ||
     * start_code_prefix != 0x000001 || called functions throw the error
     */
    static PESPacket *getNextPesPacket(ESPacket::start_code start_code) {
        auto PES_packet_length = (unsigned short) read(16);
        if (start_code != ESPacket::start_code::program_stream_map &&
            start_code != ESPacket::start_code::padding_stream &&
            start_code != ESPacket::start_code::private_stream_2 &&
            start_code != ESPacket::start_code::ECM_stream &&
            start_code != ESPacket::start_code::EMM_stream &&
            start_code != ESPacket::start_code::program_stream_directory &&
            start_code != ESPacket::start_code::DSMCC_stream &&
            start_code != ESPacket::start_code::MMATM_E_stream) {
            marker(2, 0b10);
            auto PES_scrambling_control = (unsigned char) read(2);
            auto PES_priority = (unsigned char) read(1);
            auto data_alignment_indicator = (unsigned char) read(1);
            auto copyright = (unsigned char) read(1);
            auto original_or_copy = (unsigned char) read(1);
            auto PTS_DTS_flags = (unsigned char) read(2);
            auto ESCR_flag = (unsigned char) read(1);
            auto ES_rate_flag = (unsigned char) read(1);
            auto DSM_trick_mode_flag = (unsigned char) read(1);
            auto additional_copy_info_flag = (unsigned char) read(1);
            auto PES_CRC_flag = (unsigned char) read(1);
            auto PES_extension_flag = (unsigned char) read(1);
            auto PES_header_data_length = (unsigned char) read(8);
            PESPacket::pts_dts_fields pts_dts = handlePTSDTSFlags(PTS_DTS_flags);
            unsigned long long ESCR = ESCR_flag == 0x1 ? handleESCRFlag() : 0;
            unsigned int ES_rate = ES_rate_flag == 0x1 ? handleESRate() : 0;
            PESPacket::dsm_trick_mode_fields dsm_trick_mode = handleDSMTrickModeFlag(DSM_trick_mode_flag);
            unsigned char additional_copy_info = handleCopyInfo(additional_copy_info_flag);  //7-bit
            auto previous_PES_packet_CRC = (unsigned short) (PES_CRC_flag == 0x1 ? read(16) : 0); //16-bit
            PESPacket::PES_extension_fields pes_extension_fields = handlePESExtension(PES_extension_flag);
            while (peek(8) == 0xFF) {
                read(8);
            }
            unsigned int data_length = 0;
            unsigned char *data = nullptr;
            while (peek(24) != 0x000001) {
                data = (unsigned char *) realloc(data, sizeof(unsigned char) * (data_length + 3));
                data[data_length++] = (unsigned char) read(8);
                data[data_length++] = (unsigned char) read(8);
                data[data_length++] = (unsigned char) read(8);
            }
            return new PESPacket(ESPacket::start_code::video_stream, 0xE0, PES_packet_length, PES_scrambling_control,
                                 PES_priority, data_alignment_indicator, copyright, original_or_copy, PTS_DTS_flags,
                                 ESCR_flag, ES_rate_flag, DSM_trick_mode_flag, additional_copy_info_flag, PES_CRC_flag,
                                 PES_extension_flag, PES_header_data_length, pts_dts, ESCR, ES_rate, dsm_trick_mode,
                                 additional_copy_info,
                                 previous_PES_packet_CRC, pes_extension_fields, data_length, data);

        } else {
            throw PacketException("PESParser::getNextPesPacket: start_code not handled\n");
        }
    }

private:

    static void valueChecks(unsigned int numBits, unsigned long long expectedVal, const std::string &funcName) {
        unsigned long long readVal = read(numBits);
        if (readVal != expectedVal) {
            std::string s = "PASParser::";
            s.append(funcName);
            s.append(": bad packet! Expected value = ");
            s.append(std::to_string(expectedVal));
            s.append(", ReadVal = ");
            s.append(std::to_string(readVal));
            s.append("\n");
            throw PacketException(s);
        }
    }

    static unsigned char handleCopyInfo(unsigned char flag) {
        if (flag == 0x1) {
            mark1;
            return (unsigned char) read(7);
        }
        return 0;
    }

    static PESPacket::PES_extension_fields handlePESExtension(unsigned char flag) {
        PESPacket::PES_extension_fields out{};
        if (flag == 0x1) {
            out.PES_private_data_flag = (unsigned char) read(1);
            out.pack_header_field_flag = (unsigned char) read(1);
            out.program_packet_sequence_counter_flag = (unsigned char) read(1);
            out.P_STD_buffer_flag = (unsigned char) read(1);
            marker(3, 0b111);
            out.PES_extension_flag_2 = (unsigned char) read(1);
            if (out.PES_private_data_flag == 0x1) { read(128); }
            if (out.pack_header_field_flag == 0x1) {
                out.pack_field_length = (unsigned char) read(8);
                out.pack_header = parsePackHeader();
            }
            if (out.program_packet_sequence_counter_flag == 0x1) {
                mark1;
                out.program_packet_sequence_counter = (unsigned char) read(7);
                mark1;
                out.MPEG1_MPEG2_identifier = (unsigned char) read(1);
                out.original_stuff_length = (unsigned char) read(6);
            }
            if (out.P_STD_buffer_flag == 0x1) {
                marker(2, 0b01);
                out.P_STD_buffer_scale = (unsigned char) read(1);
                out.P_STD_buffer_size = (unsigned short) read(13);
            }
            if (out.PES_extension_flag_2 == 0x1) {
                mark1;
                out.PES_extension_field_length = (unsigned char) read(7);
                for (unsigned int i = 0; i < out.PES_extension_field_length; i++) {
                    marker(8, 0xFF);
                }
            }
        }
        return out;
    }

    static PESPacket::pack_header parsePackHeader() {
        PESPacket::pack_header out{};
        if (read(32) != 0x000001BA) {
            throw PacketException("PESParser::parsePackHeader: pack_start_code != 0x000001BA\n");
        }
        marker(2, 0b01);
        out.system_clock_reference = read(3);
        mark1;
        out.system_clock_reference = (out.system_clock_reference << 15u) + read(15);
        mark1;
        out.system_clock_reference = (out.system_clock_reference << 15u) + read(15);
        mark1;
        out.system_clock_reference = out.system_clock_reference * 300 + read(9); //Equation 2-19
        mark1;
        out.program_mux_rate = (unsigned int) read(22);
        marker(7, 0b1111111);
        auto pack_stuffing_length = (unsigned char) read(3);
        for (unsigned int i = 0; i < pack_stuffing_length; i++) {
            marker(8, 0xFF);
        }
        out.system_header = parseSystemHeader();
        return out;
    }

    static PESPacket::system_header parseSystemHeader() {
        PESPacket::system_header out{};
        if (read(32) != 0x000001BB) {
            throw PacketException("PESParser::parsePackHeader: system_header_start_code != 0x000001BB\n");
        }
        out.header_length = (unsigned short) read(16);
        mark1;
        out.rate_bound = (unsigned int) read(1);
        mark1;
        out.audio_bound = (unsigned char) read(6);
        out.fixed_flag = (unsigned char) read(1);
        out.CSPS_flag = (unsigned char) read(1);
        out.system_audio_lock_flag = (unsigned char) read(1);
        out.system_video_lock_flag = (unsigned char) read(1);
        mark1;
        out.video_bound = (unsigned char) read(5);
        out.packet_rate_restriction_flag = (unsigned char) read(1);
        marker(7, 0x7F);
        size_t malloc_size = (size_t) ((out.header_length * 8) - 47) / 25; // TODO - check calc
        out.p_std = (PESPacket::P_STD *) malloc(sizeof(PESPacket::P_STD) * malloc_size);
        out.numPSTD = malloc_size;
        unsigned int index = 0;
        while (read(1) == 0x1 && index < malloc_size) {
            out.p_std[index].stream_id = ESPacket::getStartCode((unsigned char) read(8));
            marker(2, 0b11);
            out.p_std[index].P_STD_buffer_bound_scale = (unsigned char) read(1);
            out.p_std[index].P_STD_buffer_size_bound = (unsigned short) read(13);
            index++;
        }
        return out;
    }

//TODO - implement the decoding based on the equations 2-11 and 2-12
// @Bhavesh don't worry about these for now and leave them as stub.
// These are related to presentation time and for now we are just printing frames to file.
    static PESPacket::pts_dts_fields handlePTSDTSFlags(unsigned short flag) {
        PESPacket::pts_dts_fields out{0, 0};
        if (flag == 0b10) {
            marker(4, 0b0010);
            out.PTS = read(3);
            mark1;
            out.PTS = (out.PTS << 15u) + read(15);
            mark1;
            out.PTS = (out.PTS << 15u) + read(15);
            mark1;
        }
        if (flag == 0b11) {
            marker(4, 0b0011);
            out.PTS = read(3);
            mark1;
            out.PTS = (out.PTS << 15u) + read(15);
            mark1;
            out.PTS = (out.PTS << 15u) + read(15);
            mark1;
            marker(4, 0b0001);
            out.DTS = read(3);
            mark1;
            out.DTS = (out.DTS << 15u) + read(15);
            mark1;
            out.DTS = (out.DTS << 15u) + read(15);
            mark1;
        }
        return out;
    }

//TODO - implement the decoding based on the equations 2-13, 2-14 and 2-15
// @Bhavesh don't worry about these for now and leave them as stub.
// These are related to timings and for now we are just printing frames to file.
    static unsigned long long handleESCRFlag() {
        marker(2, 0b11);
        unsigned long long out = read(3);
        mark1;
        out = (out << 15u) + read(15);
        mark1;
        out = (out << 15u) + read(15);
        mark1;
        out = out * 300 + read(9); //Equation 2-13
        mark1;
        return out;
    }

    static unsigned int handleESRate() {
        mark1;
        auto out = (unsigned int) read(22);
        read(1);
        mark1;
        return out;
    }

    static PESPacket::dsm_trick_mode_fields handleDSMTrickModeFlag(unsigned char flag) {
        PESPacket::dsm_trick_mode_fields out{PESPacket::trick_mode_control_values::reserved_control_values, 0, 0, 0, 0};
        if (flag == 1) {
            out.trick_mode_control = PESPacket::getType(read(3));
            if (out.trick_mode_control == PESPacket::trick_mode_control_values::fast_reverse ||
                out.trick_mode_control == PESPacket::trick_mode_control_values::fast_forward) {
                out.field_id = (unsigned char) read(2);
                out.intra_slice_refresh = (unsigned char) read(1);
                out.frequency_truncation = (unsigned char) read(2);
            } else if (out.trick_mode_control == PESPacket::trick_mode_control_values::slow_motion ||
                       out.trick_mode_control == PESPacket::trick_mode_control_values::slow_reverse) {
                out.rep_cntrl = (unsigned char) read(5);
            } else if (out.trick_mode_control == PESPacket::trick_mode_control_values::freeze_frame) {
                out.field_id = (unsigned char) read(2);
                marker(3, 0b111);
            } else {
                marker(5, 0b11111);
            }
        }
        return out;
    }

};