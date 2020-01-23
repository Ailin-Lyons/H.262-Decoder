//
// Created by elnsa on 2020-01-18.
//

#include <RegularStartCodes/PictureCodingExtensionPacket.h>
#include <VideoDecoder.h>
#include <Slice/SlicePacket.h>
#include "PictureDecoder.h"

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

void PictureDecoder::buildPicture() {
    do {
        SlicePacket *pictureData = (SlicePacket*) VideoDecoder::getInstance()->getNextVideoPacket(); //TODO handle the loaded packet
        pictureData->print();
    } while (VideoDecoder::getInstance()->nextVideoPacketIs(ESPacket::start_code::slice));
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

