//
// Created by elnsa on 2020-01-05.
//

#include "../TransportPacketStructure/TransportPacket.h"
#include "../TSPayloadSections/ProgramMapSection.h"
#include "ESParser.h"
#include "DescriptorParser.cpp"

class PMSParser {
public:
    /**
     * Parses the next TransportPacket as a ProgramMapSection if possible and if necessary reads additional TransportPackets
     * @return a ProgramMapSection representing the ProgramMapSection that starts in tPacket
     */
    static ProgramMapSection *getPMSPacket() {
        ESParser *esParser = ESParser::getInstance();
        unsigned char pointer_length = esParser->popNBits(8);
        for(int i = 0; i < pointer_length; i++){
            esParser->popNBits(8);
        }
        TSPayloadSections::ts_payload_header_fields headerFields = {};
        headerFields.table_id = esParser->popNBits(8);
        headerFields.t_id_type = TSPayloadSections::getTableID(headerFields.table_id);
        if (headerFields.t_id_type != TSPayloadSections::TableIDType::TS_program_map_section) {
            throw PacketException("PMSParser::getPMSPacket: unexpected table_id");
        }
        headerFields.section_syntax_indicator = esParser->popNBits(1);
        if (esParser->popNBits(1) != 0) {
            throw PacketException("PMSParser::getPMSPacket expect '0' but found '1'");
        }
        esParser->popNBits(2); //reserved
        headerFields.section_length = esParser->popNBits(12);
        int remainingSectionBytes = headerFields.section_length;
        unsigned short program_number = esParser->popNBits(16);
        esParser->popNBits(2); //reserved
        TSPayloadSections::ts_payload_version_section_fields versionSectionFields = {};
        versionSectionFields.version_number = esParser->popNBits(5);
        versionSectionFields.current_next_indicator = esParser->popNBits(1);
        versionSectionFields.section_number = esParser->popNBits(8);
        versionSectionFields.last_section_number = esParser->popNBits(8);
        esParser->popNBits(3); //reserved
        unsigned short PCR_PID = esParser->popNBits(13);
        esParser->popNBits(4); //reserved
        unsigned short program_info_length = esParser->popNBits(12);
        remainingSectionBytes -= 9; //Num bytes so far
        Descriptor::decriptor_struct program_info_descriptors = DescriptorParser::buildDescriptors(program_info_length);
        remainingSectionBytes -= program_info_length;//Num bytes for pi_descriptors
        ProgramMapSection::program_element el;
        while (remainingSectionBytes > 0) {
            unsigned char stream_type_value = esParser->popNBits(8);
            ProgramMapSection::StreamType stream_type = ProgramMapSection::getStreamType(stream_type_value);
            esParser->popNBits(3); //reserved
            unsigned short elementary_PID = esParser->popNBits(13);
            esParser->popNBits(4); //reserved
            unsigned short ES_info_length = esParser->popNBits(12);
            if (stream_type == ProgramMapSection::StreamType::video_H_262) {
                el.stream_type_value = stream_type_value;
                el.stream_type = stream_type;
                el.elementary_PID = elementary_PID;
                el.ES_info_length = ES_info_length;
                unsigned short ES_info_remaining = el.ES_info_length;
                el.descriptors = DescriptorParser::buildDescriptors(program_info_length);
            }
            remainingSectionBytes -= 5;
            remainingSectionBytes -= ES_info_length;
        }
        ProgramMapSection *out = (ProgramMapSection *) malloc(sizeof(ProgramMapSection));
        *out = ProgramMapSection(headerFields, program_number, versionSectionFields, PCR_PID, program_info_length,
                                 program_info_descriptors, el);
        return out;
    }
};
