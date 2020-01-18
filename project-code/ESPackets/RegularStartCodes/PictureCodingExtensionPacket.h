//
// Created by elnsa on 2020-01-16.
//

#ifndef PROJECT_CODE_PICTURECODINGEXTENSIONPACKET_H
#define PROJECT_CODE_PICTURECODINGEXTENSIONPACKET_H

#include "../ESPacket.h"

class PictureCodingExtensionPacket: public ESPacket {
private:
    unsigned char f_code_0_0; //4-bits
    unsigned char f_code_0_1; //4-bits
    unsigned char f_code_1_0; //4-bits
    unsigned char f_code_1_1; //4-bits
    unsigned char intra_dc_precision; //2-bits
    unsigned char picture_structure; //2-bits
    bool top_field_first;
    bool frame_pred_frame_dct;
    bool concealment_motion_vectors;
    bool q_scale_type;
    bool intra_vlc_format;
    bool alternate_scan;
    bool repeat_first_field;
    bool chroma_420_type;
    bool progressive_frame;
    bool composite_display_flag;
    bool v_axis;
    unsigned char field_sequence; //3-bits
    bool sub_carrier;
    unsigned char burst_amplitude; //7-bits
    unsigned char sub_carrier_phase; //8-bits
public:
    struct initializerStruct {
        unsigned char f_code_0_0; //4-bits
        unsigned char f_code_0_1; //4-bits
        unsigned char f_code_1_0; //4-bits
        unsigned char f_code_1_1; //4-bits
        unsigned char intra_dc_precision; //2-bits
        unsigned char picture_structure; //2-bits
        bool top_field_first;
        bool frame_pred_frame_dct;
        bool concealment_motion_vectors;
        bool q_scale_type;
        bool intra_vlc_format;
        bool alternate_scan;
        bool repeat_first_field;
        bool chroma_420_type;
        bool progressive_frame;
        bool composite_display_flag;
        bool v_axis;
        unsigned char field_sequence; //3-bits
        bool sub_carrier;
        unsigned char burst_amplitude; //7-bits
        unsigned char sub_carrier_phase; //8-bits
    };

    /**
     * Constructor
     */
    PictureCodingExtensionPacket(initializerStruct init);

    void print() override;

    bool operator==(const PictureCodingExtensionPacket &rhs) const;

    bool operator!=(const PictureCodingExtensionPacket &rhs) const;

    ~PictureCodingExtensionPacket() = default;
};


#endif //PROJECT_CODE_PICTURECODINGEXTENSIONPACKET_H
