//
// Created by bhave on 11/17/2019.
//

#ifndef DIRECTED_STUDIES_PES_PACKET_H
#define DIRECTED_STUDIES_PES_PACKET_H


#include "PESPayload.h"
#include <iostream>

/*
 * Class for representing the structure of a PESPacket
 *
 */

class PESPacket {

public:

private:
    unsigned char stream_id;
    PESPayload::start_code packet_type;
    unsigned short PES_packet_length;
    PESPayload* pesPayload;

public:
    void toString();

};


#endif //DIRECTED_STUDIES_PES_PACKET_H
