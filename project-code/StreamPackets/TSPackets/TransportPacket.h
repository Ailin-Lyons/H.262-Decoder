//
// Created by bhave on 11/19/2019.
//

#ifndef PROJECT_CODE_TRANSPORTPACKET_H
#define PROJECT_CODE_TRANSPORTPACKET_H

#include "AdaptationField.h"

/**
 * H.222.0 Table 2-2
 */

class TransportPacket {

public:

    /**
     * H.222.0 Table 2-3 - PID values
     */
    enum class PID {
        ProgramAssociationTable,
        ConditionalAccessTable,
        Reserved,
        NullPacket,
        Misc
    };

    /**
     * H.222.0 Table 2-4 - Scrambling control values
     */
    enum class TSC {
        NotScrambled,
        UserDefined
    };

    /**
     * H.222.0 Table 2-4 - Adaptation Field control values
     */
    enum class AFC {
        Reserved,
        PayloadOnly,
        AFieldOnly,
        AFieldPayload
    };

    /**
     * Returns the correct PID given parsed_pid
     *
     * @param parsed_pid
     * @return PID
     */
    static PID getPID(unsigned int parsed_pid) {
        if (parsed_pid == 0x0) {
            return PID::ProgramAssociationTable;
        } else if (parsed_pid == 0x1) {
            return PID::ConditionalAccessTable;
        } else if (parsed_pid == 0x1fff) {
            return PID::NullPacket;
        } else if (parsed_pid <= 0x000F) {
            return PID::Reserved;
        } else {
            return PID::Misc;
        }
    }

    /**
     * Returns the correct TSC given parsed_afc
     *
     * @param parsed_tsc
     * @return TSC
     */
    static TSC getTSC(unsigned char parsed_tsc) {
        if (parsed_tsc == 0) {
            return TSC::NotScrambled;
        } else {
            return TSC::UserDefined;
        }
    }

    /**
     * Returns the correct AFC given the parsed_afc
     *
     * @param parsed_afc
     * @return AFC
     */
    static AFC getAFC(unsigned char parsed_afc) {
        switch (parsed_afc) {
            case 0:
                return AFC::Reserved;
            case 1:
                return AFC::PayloadOnly;
            case 2:
                return AFC::AFieldOnly;
            default:
                return AFC::AFieldPayload;
        }
    }

    /**
     * Struct that contains all transport packet header fields
     */
    struct transport_header_fields {
        unsigned char sync_byte;
        unsigned char transport_error_indicator;
        unsigned char payload_unit_start_indicator;
        unsigned char transport_priority;
        unsigned int pid;
        PID pid_type;
        TSC transport_scrambling_control;
        AFC adaptation_field_control;
        unsigned char continuity_counter;
    };


private:
    /**
     * Fields for the Transport Packet
     */
    transport_header_fields header_fields{};
    AdaptationField adaptationField;
    size_t data_length;
    unsigned char *data;

public:
    /**
     * Constructor
     * @param thf a transport_header_field struct containing all TS packet header fields
     * @param af an adaptationField object
     * @param d an array of bytes representing data
     */
    TransportPacket(TransportPacket::transport_header_fields thf, const AdaptationField &adaptationField,
                    size_t dl, unsigned char *d);

    void print();

    bool operator==(const TransportPacket &rhs) const;

    bool operator!=(const TransportPacket &rhs) const;

    size_t getDataLength() const;

    unsigned char *getData() const;

    unsigned int getPacketPID() const;

    ~TransportPacket();
};

#endif //PROJECT_CODE_TRANSPORTPACKET_H
