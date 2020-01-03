//
// Created by bhave on 11/17/2019.
//

#ifndef DIRECTED_STUDIES_PES_PACKET_H
#define DIRECTED_STUDIES_PES_PACKET_H


#include "ESPacket.h"
#include <iostream>

/*
 * Class for representing the structure of a PESPacket
 *
 */

class PESPacket : public ESPacket {

public:

private:
    unsigned char stream_id;
    ESPacket::start_code packet_type;
    unsigned short PES_packet_length;
    ESPacket *pesPayload;
public:
    void toString();
};


#endif //DIRECTED_STUDIES_PES_PACKET_H
