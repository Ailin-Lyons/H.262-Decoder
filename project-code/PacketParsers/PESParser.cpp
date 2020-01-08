//
// Created by bhave on 1/4/2020.
//

#include "ESParser.h"

// TODO - convert macros to compilation flag based
// TODO - check to make sure that all the reserved, stuffing, marker bits are correctly skipped
#define read(n) (ESParser::getInstance()->popNBits((n)))
#define marker(x, y) (valueChecks((x), (y), __func__))
#define mark1 (valueChecks(1, 0b1, __func__))

class PESParser{
public:

    /**
     * Parses the next packet as a PESPacket if possible
     * @return PESPacket* - parsed packet
     * @throws PacketException - if packet is not a H.222.0 video stream packet : stream_id/start_code = E0-EF ||
     * start_code_prefix != 0x000001 || called functions throw the error
     */
    static PESPacket* getNextPesPacket() {
        auto returnPacket = (PESPacket*) malloc(sizeof(PESPacket));
        // TODO - remove the 0x000001 and start code reading
        if (read(24) == 0x000001) {
            unsigned char stream_id = read(8);
            ESPacket::start_code start_code = ESPacket::getStartCode(stream_id);
            if (stream_id < 0xE0 || stream_id > 0xEF) {
                throw PacketException("PESParser::getNextPesPacket: stream_id != video_stream");
            }
            unsigned short PES_packet_length = read(16);
            if (start_code != ESPacket::start_code::program_stream_map && start_code != ESPacket::start_code::padding_stream
                && start_code != ESPacket::start_code::private_stream_2 && start_code != ESPacket::start_code::ECM_stream
                && start_code != ESPacket::start_code::EMM_stream && start_code != ESPacket::start_code::program_stream_directory
                && start_code != ESPacket::start_code::DSMCC_stream && start_code != ESPacket::start_code::MMATM_E_stream) {
                marker(2, 0b10);
                unsigned char PES_scrambling_control = read(2);
                unsigned char PES_priority = read(1);
                unsigned char data_alignment_indicator = read(1);
                unsigned char copyright = read(1);
                unsigned char original_or_copy = read(1);
                unsigned char PTS_DTS_flags = read(2);
                unsigned char ESCR_flag = read(1);
                unsigned char ES_rate_flag = read(1);
                unsigned char DSM_trick_mode_flag = read(1);
                unsigned char additional_copy_info_flag = read(1);
                unsigned char PES_CRC_flag = read(1);
                unsigned char PES_extension_flag = read(1);
                unsigned char PES_header_data_length = read(8);
                PESPacket::pts_dts_fields pts_dts = handlePTSDTSFlags(PTS_DTS_flags);
                unsigned long long ESCR = ESCR_flag == 0x1 ? handleESCRFlag() : 0;
                unsigned int ES_rate = ES_rate_flag == 0x1 ? handleESRate() : 0;
                PESPacket::dsm_trick_mode_fields dsm_trick_mode = handleDSMTrickModeFlag(DSM_trick_mode_flag);
                unsigned char additional_copy_info = handleCopyInfo(additional_copy_info_flag);  //7-bit
                unsigned short previous_PES_packet_CRC = PES_CRC_flag == 0x1 ? read(16) : 0; //16-bit
                PESPacket::PES_extension_fields pes_extension_fields = handlePESExtension(PES_extension_flag);
                //TODO - stuffing and data
            } else {
                //TODO - this is where we have the branching case for the other start_codes
                // for now throw an exception
                throw PacketException("PESParser::getNextPesPacket: start_code falls under weird start codes");
            }
        } else {
            throw PacketException("PESParser::getNextPesPacket: packet_start_code_prefix != 0x000001");
        }
        return returnPacket;
    }

private:
    static void valueChecks(unsigned int numBits, unsigned long long expectedVal, const std::string& funcName) {
        unsigned long long readVal = read(numBits);
        if(readVal != expectedVal) {
            std::string s = "PASParser::";
            s.append(funcName);
            s.append(": bad packet! Expected value = ");
            s.append(std::to_string(expectedVal));
            s.append(", ReadVal = ");
            s.append(std::to_string(readVal));
            throw PacketException(s);
        }
    }

    static unsigned char handleCopyInfo(unsigned char flag) {
        if (flag == 0x1) {
            mark1;
            return read(7);
        }
        return 0;
    }

    static PESPacket::PES_extension_fields handlePESExtension(unsigned char flag) {
        PESPacket::PES_extension_fields out{};
        if (flag == 0x1) {
            out.PES_private_data_flag = read(1);
            out.pack_header_field_flag = read(1);
            out.program_packet_sequence_counter_flag = read(1);
            out.P_STD_buffer_flag = read(1);
            marker(3, 0b111);
            out.PES_extension_flag_2 = read(1);
            if (out.PES_private_data_flag == 0x1) {read(128);}
            if (out.pack_header_field_flag == 0x1) {
                out.pack_field_length = read(8);
                out.pack_header = parsePackHeader();
            }
            if (out.program_packet_sequence_counter_flag == 0x1) {
                mark1;
                out.program_packet_sequence_counter = read(7);
                mark1;
                out.MPEG1_MPEG2_identifier = read(1);
                out.original_stuff_length = read(6);
            }
            if (out.P_STD_buffer_flag == 0x1) {
                marker(2, 0b01);
                out.P_STD_buffer_scale = read(1);
                out.P_STD_buffer_size = read(13);
            }
            if (out.PES_extension_flag_2 == 0x1) {
                mark1;
                out.PES_extension_field_length = read(7);
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
            throw PacketException("PESParser::parsePackHeader: pack_start_code != 0x000001BA");
        }
        marker(2, 0b01);
        out.system_clock_reference = read(3);
        mark1;
        out.system_clock_reference = out.system_clock_reference << 15 + read(15);
        mark1;
        out.system_clock_reference = out.system_clock_reference << 15 + read(15);
        mark1;
        out.system_clock_reference = out.system_clock_reference * 300 + read(9); //Equation 2-19
        mark1;
        out.program_mux_rate = read(22);
        marker(7, 0b1111111);
        unsigned char pack_stuffing_length = read(3);
        for (unsigned int i = 0; i < pack_stuffing_length; i++) {
            marker(8, 0xFF);
        }
        out.system_header = parseSystemHeader();
        return out;
    }

    static PESPacket::system_header parseSystemHeader() {
        PESPacket::system_header out{};
        if (read(32) != 0x000001BB) {
            throw PacketException("PESParser::parsePackHeader: system_header_start_code != 0x000001BB");
        }
        out.header_length = read(16);
        mark1;
        out.rate_bound = read(1);
        mark1;
        out.audio_bound = read(6);
        out.fixed_flag = read(1);
        out.CSPS_flag = read(1);
        out.system_audio_lock_flag = read(1);
        out.system_video_lock_flag = read(1);
        mark1;
        out.video_bound = read(5);
        out.packet_rate_restriction_flag = read(1);
        marker(7, 0x7F);
        size_t malloc_size = ((out.header_length * 8) - 47) / 25; // TODO - check calc
        out.p_std = (PESPacket::P_STD*) malloc(sizeof(PESPacket::P_STD) * malloc_size);
        unsigned int index = 0;
        while (read(1) == 0x1 && index < malloc_size) {
            out.p_std[index].stream_id = ESPacket::getStartCode(read(8));
            marker(2, 0b11);
            out.p_std[index].P_STD_buffer_bound_scale = read(1);
            out.p_std[index].P_STD_buffer_size_bound = read(13);
            index++;
        }
        return out;
    }

    //TODO - implement the decoding based on the equations 2-11 and 2-12
    static PESPacket::pts_dts_fields handlePTSDTSFlags(unsigned short flag) {
        PESPacket::pts_dts_fields out{0,0};
        if (flag == 0b10) {
            marker(4, 0b0010);
            out.PTS = read(3);
            mark1;
            out.PTS = out.PTS << 15 + read(15);
            mark1;
            out.PTS = out.PTS << 15 + read(15);
            mark1;
        }
        if (flag == 0b11) {
            marker(4, 0b0011);
            out.PTS = read(3);
            mark1;
            out.PTS = out.PTS << 15 + read(15);
            mark1;
            out.PTS = out.PTS << 15 + read(15);
            mark1;
            marker(4, 0b0001);
            out.DTS = read(3);
            mark1;
            out.DTS = out.DTS << 15 + read(15);
            mark1;
            out.DTS = out.DTS << 15 + read(15);
            mark1;
        }
        return out;
    }
    //TODO - implement the decoding based on the equations 2-13, 2-14 and 2-15
    static unsigned long long handleESCRFlag() {
        marker(2, 0b11);
        unsigned long long out = read(3);
        mark1;
        out = out << 15 + read(15);
        mark1;
        out = out << 15 + read(15);
        mark1;
        out = out * 300 + read(9); //Equation 2-13
        mark1;
        return out;
    }

    static unsigned int handleESRate() {
        mark1;
        unsigned int out = read(22);
        read(1);
        mark1;
        return out;
    }

    static PESPacket::dsm_trick_mode_fields handleDSMTrickModeFlag(unsigned char flag) {
        PESPacket::dsm_trick_mode_fields out{PESPacket::trick_mode_control_values::reserved_control_values,0,0,0,0};
        if (flag == 1) {
            out.trick_mode_control = PESPacket::getType(read(3));
            if (out.trick_mode_control == PESPacket::trick_mode_control_values::fast_reverse ||
            out.trick_mode_control == PESPacket::trick_mode_control_values::fast_forward) {
                out.field_id = read(2);
                out.intra_slice_refresh = read(1);
                out.frequency_truncation = read(2);
            }
            else if (out.trick_mode_control == PESPacket::trick_mode_control_values::slow_motion ||
            out.trick_mode_control == PESPacket::trick_mode_control_values::slow_reverse) {
                out.rep_cntrl = read(5);
            }
            else if (out.trick_mode_control == PESPacket::trick_mode_control_values::freeze_frame ) {
                out.field_id = read(2);
                marker(3, 0b111);
            }
            else {
                marker(5, 0b11111);
            }
        }
        return out;
    }
};