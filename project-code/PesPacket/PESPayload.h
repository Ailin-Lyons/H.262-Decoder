//
// Created by elnsa on 2019-12-29.
//

#ifndef PROJECT_CODE_PESPAYLOAD_H
#define PROJECT_CODE_PESPAYLOAD_H

//#include "PESPacket.h"

#include <iostream>

class PESPayload {
public:
    /**
     * The 8-bit start_code determines how the packet is to be interpreted
     * This enum contains all interpretations described in H.222.0 and H.262
     * Only some of these packet types are handled
     */
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

    virtual void toString() = 0;

    static start_code GetStartCode(unsigned char id) {
        if (id >= 0x01 && id <= 0xAF) return PESPayload::start_code::slice;
        if (id >= 0xC0 && id <= 0xDF) return PESPayload::start_code::audio_stream;
        if (id >= 0xE0 && id <= 0xEF) return PESPayload::start_code::video_stream;
        if (id >= 0xFA && id <= 0xFE) return PESPayload::start_code::reserved_data_stream;
        switch (id) {
            case 0x00 :
                return PESPayload::start_code::picture;
            case 0xB0 :
            case 0xB1 :
                return PESPayload::start_code::reserved_code;
            case 0xB2 :
                return PESPayload::start_code::user_data;
            case 0xB3 :
                return PESPayload::start_code::sequence_header;
            case 0xB4 :
                return PESPayload::start_code::sequence_error;
            case 0xB5 :
                return PESPayload::start_code::extension;
            case 0xB6 :
                return PESPayload::start_code::reserved_code;
            case 0xB7 :
                return PESPayload::start_code::sequence_end;
            case 0xB8 :
                return PESPayload::start_code::group;
            case 0xBC :
                return PESPayload::start_code::program_stream_map;
            case 0xBD :
                return PESPayload::start_code::private_stream_1;
            case 0xBE :
                return PESPayload::start_code::padding_stream;
            case 0xBF :
                return PESPayload::start_code::private_stream_2;
            case 0xF0 :
                return PESPayload::start_code::ECM_stream;
            case 0xF1 :
                return PESPayload::start_code::EMM_stream;
            case 0xF2 :
                return PESPayload::start_code::DSMCC_stream;
            case 0xF3 :
                return PESPayload::start_code::MMHM_stream;
            case 0xF4 :
                return PESPayload::start_code::MMATM_A_stream;
            case 0xF5 :
                return PESPayload::start_code::MMATM_B_stream;
            case 0xF6 :
                return PESPayload::start_code::MMATM_C_stream;
            case 0xF7 :
                return PESPayload::start_code::MMATM_D_stream;
            case 0xF8 :
                return PESPayload::start_code::MMATM_E_stream;
            case 0xF9 :
                return PESPayload::start_code::ancillary_stream;
            case 0xFF :
                return PESPayload::start_code::program_stream_directory;
            default :
                std::cerr << "PESPacket::Unexpected stream_id: " << id << std::endl;
                throw; // TODO throw an error
        }
    }

/*
 * Only returns true if sc is a PESPayload::start_code that is handled by this decoder
 */
    static bool IsHandled(PESPayload::start_code sc) {
        switch (sc) {
            default:
                return false;
            case PESPayload::start_code::picture:
            case PESPayload::start_code::slice:
            case PESPayload::start_code::sequence_header:
            case PESPayload::start_code::extension:
            case PESPayload::start_code::group:
            case PESPayload::start_code::video_stream:
                return true;
        }

    }

private:
    start_code payload_type;
};


#endif //PROJECT_CODE_PESPAYLOAD_H