//
// Created by elnsa on 2020-01-18.
//

#ifndef PROJECT_CODE_PICTUREDECODER_H
#define PROJECT_CODE_PICTUREDECODER_H


#include <../StreamPackets/ESPackets/RegularStartCodes/PictureHeaderPacket.h>
#include "../StreamPackets/ESPackets/RegularStartCodes/PictureCodingExtensionPacket.h"
#include "../PictureDecoder/Slice/MacroblockModes.h"
#include "../PictureDecoder/Slice/CodedBlockPattern.h"
#include "HPicture.h"

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
    PictureDecoder() = default;
    /**
     * Functions:
     */
    HPicture * buildPicture();
    void updateMacroBlockModes(MacroblockModes *mbmodes, size_t address_increment);
    void updateCodedBlockPattern(CodedBlockPattern *cbPattern);
    void resetDctDcPred();
    /**
     * Setters:
     */
    void setClosedGop(bool closedGop);
    void setBrokenLink(bool brokenLink);
    void setTemporalReference(unsigned short temporalReference);
    void setPictureCodingType(PictureHeaderPacket::picture_coding_types pictureCodingType);
    void setFCode00(unsigned char fCode00);
    void setFCode01(unsigned char fCode01);
    void setFCode10(unsigned char fCode10);
    void setFCode11(unsigned char fCode11);
    void setIntraDcPrecision(PictureCodingExtensionPacket::intra_dc_precision_bits intraDcPrecision);
    void setPictureStructure(PictureCodingExtensionPacket::picture_structure_types pictureStructure);
    void setTopFieldFirst(bool topFieldFirst);
    void setFramePredFrameDct(bool framePredFrameDct);
    void setConcealmentMotionVectors(bool concealmentMotionVectors);
    void setMacroblockIntra(bool macroblockIntra);
    void setMacroblockPattern(bool macroblockPattern);
    void setQScaleType(bool qScaleType);
    void setIntraVlcFormat(bool intraVlcFormat);
    void setAlternateScan(bool alternateScan);
    void setRepeatFirstField(bool repeatFirstField);
    void setChroma420Type(bool chroma420Type);
    void setProgressiveFrame(bool progressiveFrame);
    void setFrameMotionType(unsigned char frameMotionType);
    void setFieldMotionType(unsigned char fieldMotionType);
    void setSpatialTemporalWeightClass(unsigned char spatialTemporalWeightClass);
    void setCbp(unsigned char coded_block_pattern);
    void setCodedBlockPattern1(unsigned char codedBlockPattern1);
    void setCodedBlockPattern2(unsigned char codedBlockPattern2);
    void setDctDcPred(size_t i, unsigned int val);
    /**
     * Getters:
     */
    PictureHeaderPacket::picture_coding_types getPictureCodingType() const;
    unsigned char getFCode00() const;
    unsigned char getFCode01() const;
    unsigned char getFCode10() const;
    unsigned char getFCode11() const;
    PictureCodingExtensionPacket::picture_structure_types getPictureStructure() const;
    bool isFramePredFrameDct() const;
    bool isConcealmentMotionVectors() const;
    bool isMacroblockIntra() const;
    bool isMacroblockPattern() const;
    bool isIntraVlcFormat() const;
    unsigned char getFrameMotionType() const;
    unsigned char getFieldMotionType() const;
    unsigned char getSpatialTemporalWeightClass() const;
    unsigned char getCbp() const;
    unsigned char getCodedBlockPattern1() const;
    unsigned char getCodedBlockPattern2() const;
    int getDctDcPred(size_t i);
};


#endif //PROJECT_CODE_PICTUREDECODER_H
