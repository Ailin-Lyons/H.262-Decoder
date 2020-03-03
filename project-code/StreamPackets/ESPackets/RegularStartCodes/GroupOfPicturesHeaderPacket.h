//
// Created by elnsa on 2019-12-29.
//

#ifndef DIRECTED_STUDIES_GROUPPAYLOAD_H
#define DIRECTED_STUDIES_GROUPPAYLOAD_H

#include "../ESPacket.h"

class GroupOfPicturesHeaderPacket : public ESPacket {
private:
    unsigned int time_code; //25-bits
    bool closed_gop; //1-bit
    bool broken_link; //1-bit

public:
    struct initializerStruct {
        unsigned int time_code; //25-bits
        bool closed_gop; //1-bit
        bool broken_link; //1-bit
    };

    /**
     * Constructor
     */
    explicit GroupOfPicturesHeaderPacket(initializerStruct init);

    void print() override;

    bool operator==(const GroupOfPicturesHeaderPacket &rhs) const;

    bool operator!=(const GroupOfPicturesHeaderPacket &rhs) const;

    ~GroupOfPicturesHeaderPacket() = default;

    bool isClosedGop() const;

    bool isBrokenLink() const;
};


#endif //DIRECTED_STUDIES_GROUPPAYLOAD_H
