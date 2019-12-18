//
// Created by bhave on 11/19/2019.
//

#include <cstdio>
#include "TransportPacket.h"


TransportPacket::TransportPacket(transport_header_fields thf, AdaptationField *af,
                                 char *d) {
    // TODO: Why assign each field separately when you can just do a direct assignment for thf??
//    header_fields.sync_byte = thf.sync_byte;
//    header_fields.transport_error_indicator = thf.transport_error_indicator;
//    header_fields.payload_unit_start_indicator = thf.payload_unit_start_indicator;
//    header_fields.transport_priority = thf.transport_priority;
//    header_fields.transport_scrambling_control = thf.transport_scrambling_control;
//    header_fields.adaptation_field_control = thf.adaptation_field_control;
//    header_fields.continuity_counter = thf.continuity_counter;
    header_fields = thf;
    adaptationField = nullptr;
    adaptationField = af;    //TODO: adaptationField initialization
    data = d;
//    std::printf(
//            "TransportHeader:\nsync: %hhx, tei: %hhx, pusi: %hhx, tp: %hhx, pid: %hx, tsc: %hhx, afc: %hhx, cc: %hhx, afptr: %x, dataptr: %x\n \n",
//            header_fields.sync_byte, header_fields.transport_error_indicator,
//            header_fields.payload_unit_start_indicator, header_fields.transport_priority,
//            header_fields.pid, header_fields.transport_scrambling_control, header_fields.adaptation_field_control,
//            header_fields.continuity_counter, af, d);
    toString();
}

TransportPacket::~TransportPacket() = default;// {
//TODO: free the adaptationField resources
//}

void TransportPacket::toString() {
    std::printf(
            "TransportHeader:\nsync: %hhx, tei: %hhx, pusi: %hhx, tp: %hhx, pid: %hx, tsc: %hhx, afc: %hhx, cc: %hhx, afptr: %x, dataptr: %x\n \n",
            header_fields.sync_byte, header_fields.transport_error_indicator,
            header_fields.payload_unit_start_indicator, header_fields.transport_priority,
            header_fields.pid, header_fields.transport_scrambling_control, header_fields.adaptation_field_control,
            header_fields.continuity_counter, adaptationField, data);
}