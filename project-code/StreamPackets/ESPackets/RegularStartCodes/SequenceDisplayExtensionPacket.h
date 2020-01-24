//
// Created by elnsa on 2020-01-16.
//

#ifndef PROJECT_CODE_SEQUENCEDISPLAYEXTENSIONPACKET_H
#define PROJECT_CODE_SEQUENCEDISPLAYEXTENSIONPACKET_H

#include "ExtensionPacket.h"

class SequenceDisplayExtensionPacket : public ExtensionPacket {

private:
    unsigned char video_format; //3-bits
    bool colour_description; //1-bit
    unsigned char colour_primaries; //8-bits
    unsigned char transfer_characteristics; //8-bits
    unsigned char matrix_coefficients; //8-bits
    unsigned short display_horizontal_size; //14-bits
    unsigned short display_vertical_size; //14-bits

public:
    struct initializerStruct {
        unsigned char video_format; //3-bits
        bool colour_description; //1-bit
        unsigned char colour_primaries; //8-bits
        unsigned char transfer_characteristics; //8-bits
        unsigned char matrix_coefficients; //8-bits
        unsigned short display_horizontal_size; //14-bits
        unsigned short display_vertical_size; //14-bits
    };

    /**
     * Constructor
     */
    SequenceDisplayExtensionPacket(initializerStruct init);

    void print() override;

    bool operator==(const SequenceDisplayExtensionPacket &rhs) const;

    bool operator!=(const SequenceDisplayExtensionPacket &rhs) const;

    ~SequenceDisplayExtensionPacket() = default;

};


#endif //PROJECT_CODE_SEQUENCEDISPLAYEXTENSIONPACKET_H
