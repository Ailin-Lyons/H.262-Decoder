//
// Created by elnsa on 2019-12-29.
//

#ifndef DIRECTED_STUDIES_SLICEPAYLOAD_H
#define DIRECTED_STUDIES_SLICEPAYLOAD_H

#include "../../StreamPackets/ESPackets/ESPacket.h"
#include "Macroblock.h"

/**
 * This class represents a slice() from H262 6.2.4
 */
class Slice : public ESPacket {
private:
    unsigned char slice_vertical_position_extension;
    //unsigned char priority_breakpoint; //not handled by our decoder
    unsigned char quantiser_scale_code;
    bool slice_extension_flag;
    bool intra_slice;
    bool slice_picture_id_enable;
    unsigned char slice_picture_id;
    // extra_information_slice: A decoder conforming to this Specification that encounters extra_information_slice in a bitstream shall ignore it.
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
    explicit Slice(initializerStruct init);

    ~Slice();

    void print() override;

    bool operator==(const Slice &rhs) const;

    bool operator!=(const Slice &rhs) const;

    unsigned int getNumMacroblocks() const;

    void setNumMacroblocks(unsigned int num);

    Macroblock *getMacroblocks() const;

    void setMacroblocks(Macroblock *m);

};


#endif //DIRECTED_STUDIES_SLICEPAYLOAD_H
