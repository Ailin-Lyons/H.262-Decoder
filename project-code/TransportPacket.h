//
// Created by bhave on 11/19/2019.
//

#ifndef PROJECT_CODE_TRANSPORTPACKET_H
#define PROJECT_CODE_TRANSPORTPACKET_H

//#include <unistd.h>

/*
 * size of field <= 8, use char type
 * size of field >= 8 and <=16, use short type
 */


class TransportPacket {
    private:
        unsigned char sync_byte;
        unsigned char transport_error_indicator;
        unsigned char payload_unit_start_indicator;
        unsigned char transport_priority;
        unsigned short pid;
        unsigned char transport_scrambling_control;
        unsigned char adaptation_field_control;
        unsigned char continuity_counter;


};


#endif //PROJECT_CODE_TRANSPORTPACKET_H
