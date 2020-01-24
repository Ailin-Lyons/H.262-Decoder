//
// Created by bhave on 11/19/2019.
//

#include <iostream>
#include "TransportPacket.h"

TransportPacket::~TransportPacket() {
    free(data);
}

void TransportPacket::print() {
    printf(
            "TransportHeader:\nsync: %hhx, tei: %hhx, pusi: %hhx, tp: %hhx, pid_type: %x, program_pid: %hx, tsc: %hhx, afc: %hhx, cc: %hhx, afptr: %x, datalen: %i dataptr: %x\n \n",
            header_fields.sync_byte, header_fields.transport_error_indicator,
            header_fields.payload_unit_start_indicator, header_fields.transport_priority, header_fields.pid_type,
            header_fields.pid, header_fields.transport_scrambling_control, header_fields.adaptation_field_control,
            header_fields.continuity_counter, &adaptationField, data_length, data);
    adaptationField.print();
}

TransportPacket::TransportPacket(TransportPacket::transport_header_fields thf, const AdaptationField &adaptationField,
                                 unsigned int dl,
                                 unsigned char *d) : adaptationField(adaptationField) {
    header_fields = thf;
    data_length = dl;
    data = d;
}

bool TransportPacket::operator==(const TransportPacket &rhs) const {
    bool eq = header_fields.sync_byte == rhs.header_fields.sync_byte &&
              header_fields.transport_error_indicator == rhs.header_fields.transport_error_indicator &&
              header_fields.payload_unit_start_indicator == rhs.header_fields.payload_unit_start_indicator &&
              header_fields.transport_priority == rhs.header_fields.transport_priority &&
              header_fields.pid == rhs.header_fields.pid &&
              header_fields.pid_type == rhs.header_fields.pid_type &&
              header_fields.transport_scrambling_control == rhs.header_fields.transport_scrambling_control &&
              header_fields.adaptation_field_control == rhs.header_fields.adaptation_field_control &&
              header_fields.continuity_counter == rhs.header_fields.continuity_counter &&
              adaptationField == rhs.adaptationField &&
              data_length == rhs.data_length;
    if (!eq) return eq;
    for (int i = 0; i < data_length; i++) {
        if (data[i] != rhs.data[i]) {
            return false;
        }
    }
    return true;
}

bool TransportPacket::operator!=(const TransportPacket &rhs) const {
    return !(rhs == *this);
}

unsigned int TransportPacket::getDataLength() const {
    return data_length;
}

unsigned char *TransportPacket::getData() const {
    return data;
}

unsigned int TransportPacket::getPacketPID() const {
    return header_fields.pid;
}
