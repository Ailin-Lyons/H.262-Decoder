//
// Created by elnsa on 2019-12-29.
//

#ifndef PROJECT_CODE_PESPAYLOAD_H
#define PROJECT_CODE_PESPAYLOAD_H

#include "PESPacket.h"

class PESPayload {
public:
    PESPacket::start_code payload_type;
    void toString();
};
#endif //PROJECT_CODE_PESPAYLOAD_H
