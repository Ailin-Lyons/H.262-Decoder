//
// Created by bhave on 11/17/2019.
//

#ifndef DIRECTED_STUDIES_PES_PACKET_H
#define DIRECTED_STUDIES_PES_PACKET_H

/*
 * Class for representing the structure of a PESPacket
 *
 */

class PESPacket {

public:

    enum class start_code {
        picture,                // 0x00
        slice,                  // 0x01-0xAF
        reserved_code,          // 0xB0, 0xB1, 0xB6
        user_data,              // 0xB2
        sequence_header,        // 0xB3
        sequence_error,         // 0xB4
        extension,              // 0xB5
        sequence_end,           // 0xB7
        group,                  // 0xB8
        program_stream_map,     // 0xBC
        private_stream_1,       // 0xBD
        padding_stream,         // 0xBE
        private_stream_2,       // 0xBF
        audio_stream,           // 0xC0-0xDF    ISO/IEC 13818-3 or ISO/IEC 11172-3 audiostream number x xxxx
        video_stream,           // 0xE0-0xEF    ITU-T Rec. H.262 | ISO/IEC 13818-2 or ISO/IEC 11172-2video stream number xxxx
        ECM_stream,             // 0xF0
        EMM_stream,             // 0xF1
        DSMCC_stream,           // 0xF2         ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Annex B orISO/IEC 13818-6_DSMCC_stream
        MMHM_stream,            // 0xF3         ISO/IEC_13522_stream
        MMATM_A_stream,         // 0xF4         ITU-T Rec. H.222.1 type A
        MMATM_B_stream,         // 0xF5         ITU-T Rec. H.222.1 type B
        MMATM_C_stream,         // 0xF6         ITU-T Rec. H.222.1 type C
        MMATM_D_stream,         // 0xF7         ITU-T Rec. H.222.1 type D
        MMATM_E_stream,         // 0xF8         ITU-T Rec. H.222.1 type E
        ancillary_stream,       // 0xF9
        reserved_data_stream,   // 0xFA-0xFE
        program_stream_directory,//0xFF
    };


    unsigned int packet_start_code_prefix;
    unsigned char stream_id;
    start_code packet_type;
    unsigned short PES_packet_length;

public:
    void toString();

};


#endif //DIRECTED_STUDIES_PES_PACKET_H
