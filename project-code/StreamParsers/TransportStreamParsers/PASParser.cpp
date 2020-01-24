//
// Created by elnsa on 2020-01-05.
//

#include "../ESParser.h"
#include "../../StreamPackets/TSPayloadSections/ProgramAssociationSection.h"

#define read(n) (ESParser::getInstance()->popNBits((n)))
#define marker(x, y) (valueChecks((x), (y), __func__))

class PASParser {
public:
    /**
     * Parses the next packet as a ProgramAssociationSection if possible and if necessary reads additional TSPackets
     * @return a ProgramAssociationSection representing the the ProgramAssociationSection that starts in tPacket
     */
    static ProgramAssociationSection *getPASPacket() {
        unsigned char skipLength = read(8);
        for (unsigned int i = 0; i < skipLength; i++) {
            read(8);
        }
        unsigned char table_id = read(8);
        if (table_id != 0x00) {
            throw PacketException("PASParser::getPASPacket: table_id != 0x00\n");
        }
        unsigned char section_syntax_indicator = read(1);
        marker(3, 0b011);
        unsigned short section_length = read(12);
        TSPayloadSections::ts_payload_header_fields tsPayloadHeaderFields{table_id,
                                                                          TSPayloadSections::getTableID(table_id),
                                                                          section_syntax_indicator,
                                                                          section_length};
        unsigned short transport_stream_id = read(16);
        marker(2, 0b11);
        unsigned char version_number = read(5);
        unsigned char current_text_indicator = read(1);
        unsigned char section_number = read(8);
        unsigned char last_section_number = read(8);
        TSPayloadSections::ts_payload_version_section_fields tsPayloadVersionSectionFields{version_number,
                                                                                           current_text_indicator,
                                                                                           section_number,
                                                                                           last_section_number};
        unsigned int numPASPrograms = (section_length * 8 - (16 + 2 + 5 + 1 + 8 + 8 + 32)) / (16 + 3 + 13);
        auto PASPrograms = (ProgramAssociationSection::pas_program *) malloc(
                sizeof(ProgramAssociationSection::pas_program) * numPASPrograms);
        for (unsigned int i = 0; i < numPASPrograms; i++) {
            PASPrograms[i].program_number = read(16);
            marker(3, 0b111);
            PASPrograms[i].assosciated_pid = read(13);
        }
        read(32); //CRC_32
        return new ProgramAssociationSection(tsPayloadHeaderFields, transport_stream_id, tsPayloadVersionSectionFields,
                                             numPASPrograms, PASPrograms);
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
};
