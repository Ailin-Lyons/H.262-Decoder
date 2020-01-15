#include "../TransportPacketStructure/TransportPacket.h"
#include "../TransportPacketStructure/AdaptationField.h"
#include <sys/stat.h>
#include "AFParser.cpp"
#include "PacketException.cpp"
#include "../Util/FileInterface.h"

//
// Created by elnsa on 2019-11-19.
//
class TSParser {

public:

    /**
     * Returns the next TS Stream packet from the file as a TransportPacket object
     * @return a TransportPacket object || a null pointer if there was an error loading packet
     * @throws PacketException: if hasNextPacket returns false
     *         FileException: if rf->good() returns false
     */
    static TransportPacket *getNextPacket() {
        unsigned char file_buffer[188];
        FileInterface::getInstance()->getNextPacketData((char *) file_buffer);
        return buildTransportPacket(file_buffer);
    }

private:

    /**
     * Helper function that creates a TransportPacket at *out
     * @param packet: points to a TS Packet in binary form
     * @throws PacketException: if sync_byte != 0x47
     */
    static TransportPacket* buildTransportPacket(unsigned char *packet) {
        size_t packetIndex = 0;
        TransportPacket::transport_header_fields thf_out{};
        thf_out.sync_byte = packet[packetIndex];
        if (thf_out.sync_byte != 0x47) {
            throw PacketException("TSParser::buildTransportPacket: sync_byte error");
        }
        packetIndex++;
        thf_out.transport_error_indicator = BitManipulator::readNBits(&packet[packetIndex], 1);
        thf_out.payload_unit_start_indicator = BitManipulator::readNBitsOffset(&packet[packetIndex], 1, 1);
        thf_out.transport_priority = BitManipulator::readNBitsOffset(&packet[packetIndex], 2, 1);
        thf_out.pid = BitManipulator::readNBitsOffset(&packet[packetIndex], 3, 13);
        thf_out.pid_type = TransportPacket::getPID(thf_out.pid);
        packetIndex += 2;
        thf_out.transport_scrambling_control = TransportPacket::getTSC(
                BitManipulator::readNBits(&packet[packetIndex], 2));
        thf_out.adaptation_field_control = TransportPacket::getAFC(
                BitManipulator::readNBitsOffset(&packet[packetIndex], 2, 2));
        thf_out.continuity_counter = BitManipulator::readNBitsOffset(&packet[packetIndex], 4, 4);
        packetIndex++;
        AdaptationField adaptationField(AdaptationField::initializerStruct{});
        if (thf_out.adaptation_field_control == TransportPacket::AFC::AFieldOnly ||
            thf_out.adaptation_field_control == TransportPacket::AFC::AFieldPayload) {
            adaptationField = AFParser::generateAdaptationField(&packet[packetIndex]);
            packetIndex += adaptationField.getAdaptationFieldLength() + 1; // see H.222 2.4.3.5
        }
        auto *data = (unsigned char *) malloc(sizeof(char) * (188 - packetIndex));
        unsigned int data_length = 188 - packetIndex;
        if (thf_out.adaptation_field_control == TransportPacket::AFC::AFieldPayload ||
            thf_out.adaptation_field_control == TransportPacket::AFC::PayloadOnly) {
            for (int i = 0; packetIndex < 188; i++) {
                data[i] = (unsigned char) packet[packetIndex];
                packetIndex++;
            }
        }
        return new TransportPacket(thf_out, adaptationField, data_length, data);
    }
};
