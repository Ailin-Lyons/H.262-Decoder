//
// Created by bhave on 11/19/2019.
//

#ifndef PROJECT_CODE_TRANSPORTPACKET_H
#define PROJECT_CODE_TRANSPORTPACKET_H

//#include <unistd.h>


#include "AdaptationField.h"


class TransportPacket {

private:

    /**
     * Defining private enums for Transport packet
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

    PID getPID(unsigned short parsed_pid) {
        if (parsed_pid == 0x0) {
            return PID::ProgramAssociationTable;
        } else if (parsed_pid == 0x1) {
            return PID::ConditionalAccessTable;
        } else if (parsed_pid == 0x1fff) {
            return PID::NullPacket;
        } else if (parsed_pid <= 0x000F){
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

    TSC getTSC(unsigned char parsed_tsc) {
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

    AFC getAFC(unsigned char parsed_afc) {
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
     * Fields for the Transport Packet
     */

    unsigned char sync_byte;
    unsigned char transport_error_indicator;
    unsigned char payload_unit_start_indicator;
    unsigned char transport_priority;
    PID pid;
    TSC transport_scrambling_control;
    AFC adaptation_field_control;
    unsigned char continuity_counter;
    AdaptationField* adaptationField;

public:
    TransportPacket(unsigned char sb, unsigned char tei, unsigned char pusi, unsigned char tp,
            unsigned short pid, unsigned char tsc, unsigned char afc, unsigned char cc);
    ~TransportPacket();


};


#endif //PROJECT_CODE_TRANSPORTPACKET_H
