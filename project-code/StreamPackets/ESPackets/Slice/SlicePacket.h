//
// Created by elnsa on 2019-12-29.
//

#ifndef DIRECTED_STUDIES_SLICEPAYLOAD_H
#define DIRECTED_STUDIES_SLICEPAYLOAD_H

#include "../ESPacket.h"
#include "Macroblock.h"

class SlicePacket : public ESPacket {
private:
    unsigned char slice_vertical_position_extension;
    //unsigned char priority_breakpoint; //not handled by our decoder
    unsigned char quantiser_scale_code;
    bool slice_extension_flag;
    bool intra_slice;
    bool slice_picture_id_enable;
    unsigned char slice_picture_id;
    // extra_information_slice: A decoder conforming to this Specification that encounters extra_information_slice in a bitstream shall ignore
    unsigned int numMacroblocks;
    Macroblock *macroblocks;

public:
    struct initializerStruct {
        unsigned char stream_id;
        unsigned char slice_vertical_position_extension;
        //unsigned char priority_breakpoint; //not handled by our decoder
        unsigned char quantiser_scale_code;
        bool slice_extension_flag;
        bool intra_slice;
        bool slice_picture_id_enable;
        unsigned char slice_picture_id;
        // extra_information_slice: A decoder conforming to this Specification that encounters extra_information_slice in a bitstream shall ignore
        unsigned int numMacroblocks;
        Macroblock *macroblocks;
    };

    /**
     * Constructor
     */
    SlicePacket(initializerStruct init);

    ~SlicePacket();

    void print() override;

    bool operator==(const SlicePacket &rhs) const;

    bool operator!=(const SlicePacket &rhs) const;

};


#endif //DIRECTED_STUDIES_SLICEPAYLOAD_H
