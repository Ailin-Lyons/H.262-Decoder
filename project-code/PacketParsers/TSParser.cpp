#include "../TransportPacketStructure/TransportPacket.h"
#include "../TransportPacketStructure/AdaptationField.h"
#include <sys/stat.h>
#include "AFParser.cpp"
//#include "PacketException.cpp"
#include "../Util/FileInterface.cpp"

//using namespace std;

//
// Created by elnsa on 2019-11-19.
//
class TSParser {
//    std::ifstream *rf;
//    int file_size;
//    int num_packets;
//    char *file_buffer;
//    int index = 0;

public:

//    /**
//     * Explicit Constructor
//     * @param relative_path: relative path to load the file from with respect to TSParser.cpp
//     */
//    explicit TSParser(char *relative_path) {
//        rf = new std::ifstream(relative_path, std::ios::in | std::ios::binary);
//        file_size = getFileSize(relative_path);
//        if (!(*rf)) {
//            throw FileException("TSParser::Cannot open file!");
//        }
//        if (!isValidFile(relative_path)) {
//            throw FileException("TSParser::Invalid file!");
//        }
//        num_packets = file_size / 188;
//        file_buffer = new char[188];
//    }

//    /**
//     * Must be called before calling getNextPacket to avoid PacketException
//     * Closes the file if no more packets are available
//     * @return true iff there are additional packets in file
//     */
//    bool HasNextPacket() {
//        if (index >= num_packets) {
//            if (rf->is_open()) {
//                rf->close();
//            }
//        }
//        return index < num_packets;
//    }


    /**
     * Returns the next TS Stream packet from the file as a TransportPacket object
     * @return a TransportPacket object || a null pointer if there was an error loading packet
     * @throws PacketException: if HasNextPacket returns false
     *         FileException: if rf->good() returns false
     */
    static TransportPacket *GetNextPacket() {
        unsigned char file_buffer[188];
        auto *out = (TransportPacket *) malloc(sizeof(TransportPacket));
        FileInterface::getInstance()->getNextPacketData((char *) file_buffer);
        out[0] = buildTransportPacket(file_buffer);
        return out;
    }

private:
//    /**
//     * A helper function that determines the length of a file in bytes
//     * @param relative_path: relative path to load the file from with respect to TSParser.cpp
//     * @return length of file in bytes || -1 if error
//     */
//    static int getFileSize(char *relative_path) {
//        struct stat results;
//
//        if (stat(relative_path, &results) == 0)
//            return results.st_size;
//        else return -1;
//    }

//    /**
//     * A helper function that verifies that the input file is valid
//     * @param relative_path: relative path to load the file from with respect to TSParser.cpp
//     * @return true iff file exists and is multiple of 188 bytes
//     */
//    bool isValidFile(char *relative_path) {
//        //int file_size = TSParser::getFileSize(relative_path);
//        if (file_size == -1) {
//            return false; // Error getting file size
//        } else return file_size % 188 == 0;
//    }

    /**
     * Helper function that creates a TransportPacket object given a TS packet in binary data
     * @param packet: TS Packet in binary form
     * @return a TransportPacket Object containing all fields and data from binary packet
     * @throws PacketException: if sync_byte != 0x47
     */
    static TransportPacket buildTransportPacket(unsigned char *packet) {
        size_t packetIndex = 0;
        TransportPacket::transport_header_fields thf_out{};
        thf_out.sync_byte = packet[packetIndex];
        if (thf_out.sync_byte != 0x47) {
            throw PacketException("TSParser::buildTransportPacket: sync_byte error");
        }
        packetIndex++;
        thf_out.transport_error_indicator = BitManipulator::ReadNBits(&packet[packetIndex], 1);
        thf_out.payload_unit_start_indicator = BitManipulator::ReadNBitsOffset(&packet[packetIndex], 1, 1);
        thf_out.transport_priority = BitManipulator::ReadNBitsOffset(&packet[packetIndex], 2, 1);
        thf_out.pid = TransportPacket::getPID(BitManipulator::ReadNBitsOffset(&packet[packetIndex], 3, 13));
        packetIndex += 2;
        thf_out.transport_scrambling_control = TransportPacket::getTSC(
                BitManipulator::ReadNBits(&packet[packetIndex], 2));
        thf_out.adaptation_field_control = TransportPacket::getAFC(
                BitManipulator::ReadNBitsOffset(&packet[packetIndex], 2, 2));
        thf_out.continuity_counter = BitManipulator::ReadNBitsOffset(&packet[packetIndex], 4, 4);
        packetIndex++;
        AdaptationField adaptationField;
        if (thf_out.adaptation_field_control == TransportPacket::AFC::AFieldOnly ||
            thf_out.adaptation_field_control == TransportPacket::AFC::AFieldPayload) {
            adaptationField = AFParser::generateAdaptationField(&packet[packetIndex]);
            packetIndex += adaptationField.adaptation_field_length + 1; // see H.222 2.4.3.5
        }
        unsigned char *data = (unsigned char *) malloc(sizeof(char) * (188 - packetIndex));
        unsigned int data_length = 188 - packetIndex;
        if (thf_out.adaptation_field_control == TransportPacket::AFC::AFieldPayload ||
            thf_out.adaptation_field_control == TransportPacket::AFC::PayloadOnly) {
            for (int i = 0; packetIndex < 188; i++) {
                data[i] = (char) packet[packetIndex];
                packetIndex++;
            }
        }
        return TransportPacket(thf_out, adaptationField, data_length, data);
    }
};
