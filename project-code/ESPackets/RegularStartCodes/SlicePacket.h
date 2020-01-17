//
// Created by elnsa on 2019-12-29.
//

#ifndef DIRECTED_STUDIES_SLICEPAYLOAD_H
#define DIRECTED_STUDIES_SLICEPAYLOAD_H

#include "../ESPacket.h"

class SlicePacket : public ESPacket {

public:
    struct extraInformation{
        unsigned char extra_bit_slice;
        unsigned char extra_information_slice;
    };

private:

    unsigned int slice_start_code;
    unsigned char slice_vertical_position_extension;
    unsigned char priority_breakpoint;
    unsigned char quantiser_scale_code;
    unsigned char slice_extension_flag;
    unsigned char intra_slice;
    unsigned char slice_picture_id_enable;
    unsigned char slice_picture_id;
    size_t numExtraInfo;
    SlicePacket::extraInformation* extra_Information;
    unsigned char extra_bit_slice;

    //TODO - macroblock?

    bool operator==(const SlicePacket &rhs) const;

    bool operator!=(const SlicePacket &rhs) const;

    ~SlicePacket();

public:
    struct initializerStruct {
        unsigned char stream_id;
        unsigned int slice_start_code;
        unsigned char slice_vertical_position_extension;
        unsigned char priority_breakpoint;
        unsigned char quantiser_scale_code;
        unsigned char slice_extension_flag;
        unsigned char intra_slice;
        unsigned char slice_picture_id_enable;
        unsigned char slice_picture_id;
        size_t numExtraInfo;
        SlicePacket::extraInformation* extra_Information;
        unsigned char extra_bit_slice;
    };

    /**
     * Constructor
     */
    SlicePacket(initializerStruct init);

    void print() override;

};


#endif //DIRECTED_STUDIES_SLICEPAYLOAD_H
