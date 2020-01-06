//
// Created by elnsa on 2020-01-05.
//
#ifndef PROJECT_CODE_TSPAYLOADPACKET_H
#define PROJECT_CODE_TSPAYLOADPACKET_H

/**
 * This class contains structs and enums found across TSPayloadPackets
 */
class TSPayloadPacket {
public:
    /**
     * Categories to interpret table_id
     */
    enum class table_id_type {
        program_association_section,
        conditional_access_section,
        TS_program_map_section,
        reserved,
        user_private,
        forbidden
    }; // TODO static assign class

    /**
     * Header fields found in all TSPayloadPackets
     */
    struct ts_payload_header_fields {
        unsigned char table_id; // 8-bit, describes packet type
        table_id_type t_id_type;
        unsigned char section_syntax_indicator; // 1-bit
        unsigned int section_length; // 12-bit
    };

    /**
     * Fields found in some TSPayloadPackets such as PMS and PAS
     */
    struct ts_payload_version_section_fields {
        unsigned char version_number; // 5-bit a number that is incremented each time the contents of packet changes
        unsigned char current_next_indicator; // 1-bit whether this version is currently valid
        unsigned char section_number; // 8-bit
        unsigned char last_section_number; // 8-bit
    };
};

#endif //PROJECT_CODE_TSPAYLOADPACKET_H
