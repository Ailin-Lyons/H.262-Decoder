//
// Created by elnsa on 2020-01-05.
//
#ifndef PROJECT_CODE_TSPAYLOADSECTIONS_H
#define PROJECT_CODE_TSPAYLOADSECTIONS_H

#include "../PacketParsers/PacketException.cpp"

/**
 * This class contains structs and enums found across TSPayloadSections
 */
class TSPayloadSections {
public:
    /**
     * Categories to interpret table_id
     */
    enum class TableIDType {
        program_association_section,
        conditional_access_section,
        TS_program_map_section,
        reserved,
        user_private
    };

    static TableIDType getTableID(unsigned char table_id) {
        switch (table_id) {
            case 0x00:
                return TableIDType::program_association_section   ;
            case 0x01:
                return TableIDType::conditional_access_section;
            case 0x02:
                return TableIDType::TS_program_map_section;
            case 0xFF:
                throw PacketException("TSPayloadSections::getTableID Forbidden table_id");
            default:
                if(0x03 <= table_id <= 0x3F){
                    return TableIDType::reserved;
                }
        }
        return TableIDType::user_private;
    };

    /**
     * Header fields found in all TSPayloadSections
     */
    struct ts_payload_header_fields {
        unsigned char table_id; // 8-bit, describes packet type
        TableIDType t_id_type;
        unsigned char section_syntax_indicator; // 1-bit
        unsigned short section_length; // 12-bit
    };

    /**
     * Fields found in some TSPayloadSections such as PMS and PAS
     */
    struct ts_payload_version_section_fields {
        unsigned char version_number; // 5-bit a number that is incremented each time the contents of packet changes
        unsigned char current_next_indicator; // 1-bit whether this version is currently valid
        unsigned char section_number; // 8-bit
        unsigned char last_section_number; // 8-bit
    };
};

#endif //PROJECT_CODE_TSPAYLOADSECTIONS_H
