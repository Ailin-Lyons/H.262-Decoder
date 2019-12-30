//
// Created by bhave on 11/17/2019.
//

#include "PESPacket.h"

//TODO implement toString (including calling children)
void PESPacket::toString() {
    std::printf("TODO PESPACKET");
}

PESPayload::start_code PESPacket::GetStartCode(unsigned char id) {
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
bool PESPacket::IsHandled(PESPayload::start_code sc) {
    switch (sc) {
        default: return false;
        case PESPayload::start_code::picture:
        case PESPayload::start_code::slice:
        case PESPayload::start_code::sequence_header:
        case PESPayload::start_code::extension:
        case PESPayload::start_code::group:
        case PESPayload::start_code::video_stream:
            return true;
    }
}
