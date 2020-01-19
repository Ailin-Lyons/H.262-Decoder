//
// Created by elnsa on 2020-01-18.
//

#include <RegularStartCodes/PictureCodingExtensionPacket.h>
#include <VideoDecoder.h>
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
        ESPacket *pictureData = VideoDecoder::getInstance()->getNextVideoPacket(); //TODO handle the loaded packet
        printf("TODO loadPictureData: slice with ID %x\n", pictureData->getStreamId());
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

