//
// Created by bhave on 11/19/2019.
//

#ifndef PROJECT_CODE_TRANSPORTPACKET_H
#define PROJECT_CODE_TRANSPORTPACKET_H
#include "AdaptationField.h"


class TransportPacket {

public:
    /**
     * Defining enums for Transport packet
     */
    enum class PID {
        ProgramAssociationTable,
        ConditionalAccessTable,
        Reserved,
        NullPacket,
        Misc
    };

    enum class TSC {
        NotScrambled,
        UserDefined
    };

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
    static PID getPID(unsigned short parsed_pid) {
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
     * @return
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

    /**
     * Fields for the Transport Packet
     */
    transport_header_fields header_fields{};
    AdaptationField adaptationField;
    unsigned int data_length;
    unsigned char *data;

    /**
     * Constructor
     * @param thf a transport_header_field struct containing all TS packet header fields
     * @param af an adaptationField object
     * @param d an array of bytes representing data
     */
    TransportPacket(transport_header_fields thf, const AdaptationField& af, unsigned int dl, unsigned char *d);

    void toString();

    //~TransportPacket(); //TODO fix TSParser and then un-comment
};

#endif //PROJECT_CODE_TRANSPORTPACKET_H
