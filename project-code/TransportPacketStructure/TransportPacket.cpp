//
// Created by bhave on 11/19/2019.
//

#include <iostream>
#include "TransportPacket.h"

TransportPacket::~TransportPacket() {
    free(data);
}

void TransportPacket::toString() {
    std::printf(
            "TransportHeader:\nsync: %hhx, tei: %hhx, pusi: %hhx, tp: %hhx, pid_type: %x, program_pid: %hx, tsc: %hhx, afc: %hhx, cc: %hhx, afptr: %x, datalen: %i dataptr: %x\n \n",
            header_fields.sync_byte, header_fields.transport_error_indicator,
            header_fields.payload_unit_start_indicator, header_fields.transport_priority, header_fields.pid_type,
            header_fields.pid, header_fields.transport_scrambling_control, header_fields.adaptation_field_control,
            header_fields.continuity_counter, &adaptationField, data_length, data);
    adaptationField.toString();
}

TransportPacket::TransportPacket(TransportPacket::transport_header_fields thf, const AdaptationField& af, unsigned int dl, unsigned char *d) {
    header_fields = thf;
    adaptationField = af;
    data = d;
    data_length = dl;
}
