//
// Created by elnsa on 2020-01-18.
//

#include <../StreamPackets/ESPackets/RegularStartCodes/PictureCodingExtensionPacket.h>
#include <VideoDecoder.h>
#include "DecodingStages/InverseScanner.h"
#include "DecodingStages/InverseQuantiser.h"
#include "DecodingStages/InverseDCTransformer.h"
#include "DecodingStages/AlternateQuantiser.h"

HPicture *PictureDecoder::decodePicture() {
    HPicture* picture = new HPicture();
    do {
        picture->addSlice((Slice *) VideoDecoder::getInstance()->getNextVideoPacket());
    } while (VideoDecoder::getInstance()->nextVideoPacketIs(ESPacket::start_code::slice));
    InverseScanner::performInverseScan(picture, alternate_scan);
    //InverseQuantiser::performInverseQuantisation(picture);
    AlternateQuantiser::performInverseQuantisation(picture);
    /**
     * Different IDCT implementations can be chosen here:
     */
        //InverseDCTransformer::performIDCTNaive(picture);
        InverseDCTransformer::performIDCTThreaded(picture);
    /**
     *
     */
     // TODO motion compensation if applicable
    for(size_t i = 0; i < picture->getNumSlices(); i++){
        picture->getSlices()[i]->print();
    }
    return picture;
}

void PictureDecoder::updateMacroBlockModes(MacroblockModes *mbmodes, size_t address_increment) {
    if (address_increment > 1) {
        resetDctDcPred(); // resetting dct_dc_pred as per Table 7-2
    }
    setMacroblockPattern(mbmodes->isMacroblockPattern());
    setMacroblockIntra(mbmodes->isMacroblockIntra());
    setFrameMotionType(mbmodes->getFrameMotionType());
    setFieldMotionType(mbmodes->getFieldMotionType());
    setSpatialTemporalWeightClass(mbmodes->getSpatialTemporalWeightClasses());
}

void PictureDecoder::updateCodedBlockPattern(CodedBlockPattern *cbPattern) {
    setCbp(cbPattern->getCbp());
    setCodedBlockPattern1(cbPattern->getCodedBlockPattern1());
    setCodedBlockPattern2(cbPattern->getCodedBlockPattern2());
}

void PictureDecoder::resetDctDcPred() {
    switch (intra_dc_precision) {
        case PictureCodingExtensionPacket::intra_dc_precision_bits::p_8:
            dct_dc_pred[0] = dct_dc_pred[1] = dct_dc_pred[2] = 128;
            break;
        case PictureCodingExtensionPacket::intra_dc_precision_bits::p_9:
            dct_dc_pred[0] = dct_dc_pred[1] = dct_dc_pred[2] = 256;
            break;
        case PictureCodingExtensionPacket::intra_dc_precision_bits::p_10:
            dct_dc_pred[0] = dct_dc_pred[1] = dct_dc_pred[2] = 512;
            break;
        case PictureCodingExtensionPacket::intra_dc_precision_bits::p_11:
            dct_dc_pred[0] = dct_dc_pred[1] = dct_dc_pred[2] = 1024;
            break;
        default:
            throw PacketException("PictureDecoder::resetDctDcPred: reset failed");
    }
}

/**
 * Getters & Setters
 */

void PictureDecoder::setClosedGop(bool closedGop) {
    closed_gop = closedGop;
}

void PictureDecoder::setBrokenLink(bool brokenLink) {
    broken_link = brokenLink;
}

void PictureDecoder::setTemporalReference(unsigned short temporalReference) {
    temporal_reference = temporalReference;
}

void PictureDecoder::setPictureCodingType(PictureHeaderPacket::picture_coding_types pictureCodingType) {
    picture_coding_type = pictureCodingType;
}

void PictureDecoder::setFCode00(unsigned char fCode00) {
    f_code_0_0 = fCode00;
}

void PictureDecoder::setFCode01(unsigned char fCode01) {
    f_code_0_1 = fCode01;
}

void PictureDecoder::setFCode10(unsigned char fCode10) {
    f_code_1_0 = fCode10;
}

void PictureDecoder::setFCode11(unsigned char fCode11) {
    f_code_1_1 = fCode11;
}

void PictureDecoder::setTopFieldFirst(bool topFieldFirst) {
    top_field_first = topFieldFirst;
}

void PictureDecoder::setFramePredFrameDct(bool framePredFrameDct) {
    frame_pred_frame_dct = framePredFrameDct;
}

void PictureDecoder::setConcealmentMotionVectors(bool concealmentMotionVectors) {
    concealment_motion_vectors = concealmentMotionVectors;
}

void PictureDecoder::setQScaleType(bool qScaleType) {
    q_scale_type = qScaleType;
}

void PictureDecoder::setIntraVlcFormat(bool intraVlcFormat) {
    intra_vlc_format = intraVlcFormat;
}

void PictureDecoder::setAlternateScan(bool alternateScan) {
    alternate_scan = alternateScan;
}

void PictureDecoder::setRepeatFirstField(bool repeatFirstField) {
    repeat_first_field = repeatFirstField;
}

void PictureDecoder::setChroma420Type(bool chroma420Type) {
    chroma_420_type = chroma420Type;
}

void PictureDecoder::setProgressiveFrame(bool progressiveFrame) {
    progressive_frame = progressiveFrame;
}

void PictureDecoder::setIntraDcPrecision(PictureCodingExtensionPacket::intra_dc_precision_bits intraDcPrecision) {
    intra_dc_precision = intraDcPrecision;
}

void PictureDecoder::setPictureStructure(PictureCodingExtensionPacket::picture_structure_types pictureStructure) {
    picture_structure = pictureStructure;
}

PictureHeaderPacket::picture_coding_types PictureDecoder::getPictureCodingType() const {
    return picture_coding_type;
}

PictureCodingExtensionPacket::picture_structure_types PictureDecoder::getPictureStructure() const {
    return picture_structure;
}

bool PictureDecoder::isFramePredFrameDct() const {
    return frame_pred_frame_dct;
}

bool PictureDecoder::isConcealmentMotionVectors() const {
    return concealment_motion_vectors;
}

unsigned char PictureDecoder::getFrameMotionType() const {
    return frame_motion_type;
}

void PictureDecoder::setFrameMotionType(unsigned char frameMotionType) {
    frame_motion_type = frameMotionType;
}

unsigned char PictureDecoder::getFieldMotionType() const {
    return field_motion_type;
}

void PictureDecoder::setFieldMotionType(unsigned char fieldMotionType) {
    field_motion_type = fieldMotionType;
}

unsigned char PictureDecoder::getSpatialTemporalWeightClass() const {
    return spatial_temporal_weight_classes;
}

void PictureDecoder::setSpatialTemporalWeightClass(unsigned char spatialTemporalWeightClass) {
    spatial_temporal_weight_classes = spatialTemporalWeightClass;
}

unsigned char PictureDecoder::getFCode00() const {
    return f_code_0_0;
}

unsigned char PictureDecoder::getFCode01() const {
    return f_code_0_1;
}

unsigned char PictureDecoder::getFCode10() const {
    return f_code_1_0;
}

unsigned char PictureDecoder::getFCode11() const {
    return f_code_1_1;
}

bool PictureDecoder::isMacroblockIntra() const {
    return macroblock_intra;
}

void PictureDecoder::setMacroblockIntra(bool macroblockIntra) {
    macroblock_intra = macroblockIntra;
}

bool PictureDecoder::isMacroblockPattern() const {
    return macroblock_pattern;
}

void PictureDecoder::setMacroblockPattern(bool macroblockPattern) {
    macroblock_pattern = macroblockPattern;
}

unsigned char PictureDecoder::getCbp() const {
    return cbp;
}

void PictureDecoder::setCbp(unsigned char coded_block_pattern) {
    PictureDecoder::cbp = coded_block_pattern;
}

unsigned char PictureDecoder::getCodedBlockPattern1() const {
    return coded_block_pattern_1;
}

void PictureDecoder::setCodedBlockPattern1(unsigned char codedBlockPattern1) {
    coded_block_pattern_1 = codedBlockPattern1;
}

unsigned char PictureDecoder::getCodedBlockPattern2() const {
    return coded_block_pattern_2;
}

void PictureDecoder::setCodedBlockPattern2(unsigned char codedBlockPattern2) {
    coded_block_pattern_2 = codedBlockPattern2;
}

int PictureDecoder::getDctDcPred(size_t i) {
    return dct_dc_pred[i];
}

void PictureDecoder::setDctDcPred(size_t i, int val) {
    dct_dc_pred[i] = val;
}

bool PictureDecoder::isIntraVlcFormat() const {
    return intra_vlc_format;
}

PictureCodingExtensionPacket::intra_dc_precision_bits PictureDecoder::getIntraDcPrecision() const {
    return intra_dc_precision;
}

bool PictureDecoder::isQScaleType() const {
    return q_scale_type;
}

