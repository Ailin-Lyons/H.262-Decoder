//
// Created by elnsa on 2020-01-18.
//

#ifndef PROJECT_CODE_PICTUREDECODER_H
#define PROJECT_CODE_PICTUREDECODER_H


#include <../ESPackets/RegularStartCodes/PictureHeaderPacket.h>
#include "../ESPackets/RegularStartCodes/PictureCodingExtensionPacket.h"

class PictureDecoder {
private:
    bool closed_gop;
    bool broken_link;
    unsigned short temporal_reference;
    PictureHeaderPacket::picture_coding_types picture_coding_type;
    unsigned char f_code_0_0; //4-bits
    unsigned char f_code_0_1; //4-bits
    unsigned char f_code_1_0; //4-bits
    unsigned char f_code_1_1; //4-bits
    PictureCodingExtensionPacket::intra_dc_precision_bits intra_dc_precision;
    PictureCodingExtensionPacket::picture_structure_types picture_structure;
    bool top_field_first;
    bool frame_pred_frame_dct;
    bool concealment_motion_vectors;
    bool q_scale_type;
    bool intra_vlc_format;
    bool alternate_scan;
    bool repeat_first_field;
    bool chroma_420_type;
    bool progressive_frame;

public:
    PictureDecoder() = default;

    void setClosedGop(bool closedGop);

    void setBrokenLink(bool brokenLink);

    void setTemporalReference(unsigned short temporalReference);

    void setPictureCodingType(PictureHeaderPacket::picture_coding_types pictureCodingType);

    PictureHeaderPacket::picture_coding_types getPictureCodingType() const;

    void buildPicture();

    void setIntraDcPrecision(PictureCodingExtensionPacket::intra_dc_precision_bits intraDcPrecision);

    void setPictureStructure(PictureCodingExtensionPacket::picture_structure_types pictureStructure);

    PictureCodingExtensionPacket::picture_structure_types getPictureStructure() const;

    void setFCode00(unsigned char fCode00);

    void setFCode01(unsigned char fCode01);

    void setFCode10(unsigned char fCode10);

    void setFCode11(unsigned char fCode11);

    void setTopFieldFirst(bool topFieldFirst);

    void setFramePredFrameDct(bool framePredFrameDct);

    bool isFramePredFrameDct() const;

    void setConcealmentMotionVectors(bool concealmentMotionVectors);

    bool isConcealmentMotionVectors() const;

    void setQScaleType(bool qScaleType);

    void setIntraVlcFormat(bool intraVlcFormat);

    void setAlternateScan(bool alternateScan);

    void setRepeatFirstField(bool repeatFirstField);

    void setChroma420Type(bool chroma420Type);

    void setProgressiveFrame(bool progressiveFrame);
};


#endif //PROJECT_CODE_PICTUREDECODER_H
