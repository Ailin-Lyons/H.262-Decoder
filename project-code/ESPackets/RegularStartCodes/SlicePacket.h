//
// Created by elnsa on 2019-12-29.
//

#ifndef DIRECTED_STUDIES_SLICEPAYLOAD_H
#define DIRECTED_STUDIES_SLICEPAYLOAD_H

#include "../ESPacket.h"

class SlicePacket : public ESPacket {

private:
    //TODO fields

public:
    struct initializerStruct {
        unsigned char stream_id;
        //TODO
    };

    /**
     * Constructor
     */
    SlicePacket(initializerStruct init);

    void print() override;

    bool operator==(const SlicePacket &rhs) const;

    bool operator!=(const SlicePacket &rhs) const;

    ~SlicePacket();
};


#endif //DIRECTED_STUDIES_SLICEPAYLOAD_H
