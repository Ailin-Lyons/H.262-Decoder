//
// Created by elnsa on 2020-01-16.
//

#ifndef PROJECT_CODE_PICTURECODINGEXTENSIONPACKET_H
#define PROJECT_CODE_PICTURECODINGEXTENSIONPACKET_H

#include "ExtensionPacket.h"

class PictureCodingExtensionPacket: public ExtensionPacket {
public:
    enum class intra_dc_precision_bits{
        p_8,
        p_9,
        p_10,
        p_11
    };

    enum class picture_structure_types{
        ps_reserved,
        ps_top_field,
        ps_bottom_field,
        ps_frame_picture
    };
private:
    unsigned char f_code_0_0; //4-bits
    unsigned char f_code_0_1; //4-bits
    unsigned char f_code_1_0; //4-bits
    unsigned char f_code_1_1; //4-bits
    intra_dc_precision_bits intra_dc_precision; //2-bits
    picture_structure_types picture_structure; //2-bits
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
        intra_dc_precision_bits intra_dc_precision; //2-bits
        picture_structure_types picture_structure; //2-bits
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

    static intra_dc_precision_bits getIntraDCPrecisionType(unsigned char i_dc_p);

    static picture_structure_types getPictureStructureType(unsigned char pictureStructure);

    void print() override;

    bool operator==(const PictureCodingExtensionPacket &rhs) const;

    bool operator!=(const PictureCodingExtensionPacket &rhs) const;

    ~PictureCodingExtensionPacket() = default;

    unsigned char getFCode00() const;

    unsigned char getFCode01() const;

    unsigned char getFCode10() const;

    unsigned char getFCode11() const;

    intra_dc_precision_bits getIntraDcPrecision() const;

    picture_structure_types getPictureStructure() const;

    bool isTopFieldFirst() const;

    bool isFramePredFrameDct() const;

    bool isConcealmentMotionVectors() const;

    bool isQScaleType() const;

    bool isIntraVlcFormat() const;

    bool isAlternateScan() const;

    bool isRepeatFirstField() const;

    bool isChroma420Type() const;

    bool isProgressiveFrame() const;

    bool isCompositeDisplayFlag() const;
};


#endif //PROJECT_CODE_PICTURECODINGEXTENSIONPACKET_H
