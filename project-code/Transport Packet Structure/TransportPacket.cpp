//
// Created by bhave on 11/19/2019.
//

#include "TransportPacket.h"


TransportPacket::TransportPacket(unsigned char sb, unsigned char tei, unsigned char pusi, unsigned char tp,
                                 unsigned short pid, unsigned char tsc, unsigned char afc, unsigned char cc) {
    sync_byte = sb;
    transport_error_indicator = tei;
    payload_unit_start_indicator = pusi;
    transport_priority = tp;
    this->pid = getPID(pid);
    transport_scrambling_control = getTSC(tsc);
    adaptation_field_control = getAFC(afc);
    continuity_counter = cc;
    adaptationField = nullptr;
    //TODO: adaptationField initialization
}

TransportPacket::~TransportPacket() = default;// {
    //TODO: free the adaptationField resources
//}