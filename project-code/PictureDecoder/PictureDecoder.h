//
// Created by elnsa on 2020-01-18.
//

#ifndef PROJECT_CODE_PICTUREDECODER_H
#define PROJECT_CODE_PICTUREDECODER_H


#include <../StreamPackets/ESPackets/RegularStartCodes/PictureHeaderPacket.h>
#include "../StreamPackets/ESPackets/RegularStartCodes/PictureCodingExtensionPacket.h"
#include "../PictureDecoder/Slice/MacroblockModes.h"
#include "../PictureDecoder/Slice/CodedBlockPattern.h"
#include "Picture.h"

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
    bool macroblock_intra;
    bool macroblock_pattern;
    bool q_scale_type;
    bool intra_vlc_format;
public:
    bool isIntraVlcFormat() const;

private:
    bool alternate_scan;
    bool repeat_first_field;
    bool chroma_420_type;
    bool progressive_frame;
    unsigned char frame_motion_type;
    unsigned char field_motion_type;
    unsigned char spatial_temporal_weight_classes;
    unsigned char cbp;
    unsigned char coded_block_pattern_1;
    unsigned char coded_block_pattern_2;
    int dct_dc_pred[3];

public:
    int getDctDcPred(size_t i);

    void setDctDcPred(size_t i, unsigned int val);

    void resetDctDcPred();

    PictureDecoder() = default;

    unsigned char getFrameMotionType() const;

    void setFrameMotionType(unsigned char frameMotionType);

    unsigned char getFieldMotionType() const;

    void setFieldMotionType(unsigned char fieldMotionType);

    void setClosedGop(bool closedGop);

    void setBrokenLink(bool brokenLink);

    void setTemporalReference(unsigned short temporalReference);

    void setPictureCodingType(PictureHeaderPacket::picture_coding_types pictureCodingType);

    PictureHeaderPacket::picture_coding_types getPictureCodingType() const;

    Picture * buildPicture();

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

    unsigned char getFCode00() const;

    unsigned char getFCode01() const;

    unsigned char getFCode10() const;

    unsigned char getFCode11() const;

    bool isMacroblockIntra() const;

    void setMacroblockIntra(bool macroblockIntra);

    bool isMacroblockPattern() const;

    void setMacroblockPattern(bool macroblockPattern);

    void updateMacroBlockModes(MacroblockModes *mbmodes, size_t address_increment);

    void updateCodedBlockPattern(CodedBlockPattern *cbPattern);

    unsigned char getCbp() const;

    void setCbp(unsigned char coded_block_pattern);

    unsigned char getCodedBlockPattern1() const;

    void setCodedBlockPattern1(unsigned char codedBlockPattern1);

    unsigned char getCodedBlockPattern2() const;

    void setCodedBlockPattern2(unsigned char codedBlockPattern2);

    unsigned char getSpatialTemporalWeightClass() const;

    void setSpatialTemporalWeightClass(unsigned char spatialTemporalWeightClass);
};


#endif //PROJECT_CODE_PICTUREDECODER_H
