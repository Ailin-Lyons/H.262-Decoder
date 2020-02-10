//
// Created by elnsa on 2020-01-15.
//

#include <../StreamPackets/ESPackets/RegularStartCodes/SequenceHeaderPacket.h>
#include <../StreamPackets/ESPackets/RegularStartCodes/SequenceExtensionPacket.h>
#include <../StreamPackets/ESPackets/RegularStartCodes/GroupOfPicturesHeaderPacket.h>
#include <../StreamPackets/ESPackets/RegularStartCodes/SequenceDisplayExtensionPacket.h>
#include <../StreamPackets/ESPackets/RegularStartCodes/PictureHeaderPacket.h>
#include <../StreamPackets/ESPackets/RegularStartCodes/PictureCodingExtensionPacket.h>
#include "VideoDecoder.h"
#include "VideoInformation.h"
#include "VideoException.cpp"
#include "../Util/FileInterface.h"
#include "../Util/FileException.cpp"
#include "../StreamParsers/ESParser.h"
#include "PictureBuilder.h"
#include "../CImg283/CImg.h"

VideoDecoder *VideoDecoder::instance = nullptr;

VideoDecoder::VideoDecoder() {
    pictureDecoder = nullptr;
}

void VideoDecoder::decodeToFile(char *source, char *destination) {
    pngSequenceNumber = 0;
    pictureDecoder = new PictureDecoder();
    loadFile(source);
    printf("\n***Loading Video Information...***\n");
    loadVideoSequence();
    printf("***Loading Video Information...Done!***\n");
    printf("\n***Beginning Decoding process...***\n");
    do {
        loadExtensionUserData(0);
        do {
            makePicture(destination);
            pngSequenceNumber++;
        } while (nextVideoPacketIs(ESPacket::start_code::picture) || nextVideoPacketIs(ESPacket::start_code::group));
        if (!nextVideoPacketIs(ESPacket::start_code::sequence_end)) {
            loadVideoSequence();
        }
    } while (!nextVideoPacketIs(ESPacket::start_code::sequence_end));
    printf("\n***Decoding process done...***\n");
}

bool VideoDecoder::loadFile(char *relative_path) {
    printf("\n**Loading file: %s ***\n", relative_path);
    try {
        FileInterface::getInstance()->setInstance(relative_path);
        ESParser *esp = ESParser::getInstance();
        esp->initiateStream();
        printf("***Loading file... Done!***\n", relative_path);
        return true;
    } catch (FileException &) {
        printf("Error loading file!\n");
        return false;
    }
}

void VideoDecoder::loadVideoSequence() {
    VideoInformation *videoInfo = VideoInformation::getInstance();
    auto *seq_hed = (SequenceHeaderPacket *) getNextVideoPacket();
    if (!nextVideoPacketIs(ESPacket::start_code::extension)) {
        throw VideoException("VideoDecoder::loadVideoSequence: Unhandled coding standard");
    }
    auto *seq_ex = (SequenceExtensionPacket *) getNextVideoPacket();
    videoInfo->setHorizontalSize(seq_hed->getHVal() + (seq_ex->getHExt() << 12));
    videoInfo->setVerticalSize(seq_hed->getVVal() + (seq_ex->getVExt() << 12));
    videoInfo->setAspectRatio(seq_hed->getAspectRatioInformation());
    videoInfo->setFrameRate(seq_hed->getFrameRate(), seq_ex->getFrameExtN(), seq_ex->getFrameExtD());
    videoInfo->setBitRate((seq_ex->getBitRateExt() << 12) + seq_hed->getBitRateVal());
    videoInfo->setVBVBufSize((seq_ex->getVBVBufVal() << 10) + seq_hed->getVBVBufVal());
    if (seq_hed->getCPFlag()) throw PacketException("VideoDecoder::loadVideoSequence: Unhandled coding standard");
    if (seq_hed->isLoadIntraQuantiserMatrix() || seq_hed->isLoadNonIntraQuantiserMatrix())
        throw VideoException("VideoDecoder::loadVideoSequence: IQM NIQM not supported");
    videoInfo->setProfileLevel(seq_ex->getProfileAndLevelIndication());
    videoInfo->setProgressiveSequence(seq_ex->getProgSeq());
    videoInfo->setChromaFormat(seq_ex->getChromaFormat());
    videoInfo->setLowDelay(seq_ex->getLowDelay());
    videoInfo->print();
}

void VideoDecoder::makePicture(char *destination) {
    if (nextVideoPacketIs(ESPacket::start_code::group)) {
        loadGroupHeaderAndExtension();
        loadExtensionUserData(1);
    }
    PictureHeaderPacket::picture_coding_types pctype = loadPictureHeader();
    loadPictureCodingExtension();
    loadExtensionUserData(2);
    HPicture *decodedPicture = pictureDecoder->decodePicture();
    if (pctype != PictureHeaderPacket::picture_coding_types::intra_coded) {
        throw VideoException("temp throw videoDecoder");
    }
    savePngToFile(decodedPicture, destination);
}

bool VideoDecoder::nextVideoPacketIs(ESPacket::start_code startCode) {
    if (ESPacket::getStartCode(ESParser::getInstance()->nextESPacketID()) == ESPacket::start_code::video_stream) {
        handleVideoStream(ESParser::getInstance()->getNextPacket());
        return nextVideoPacketIs(startCode);
    }
    return ESPacket::getStartCode(ESParser::getInstance()->nextESPacketID()) == startCode;
}

ESPacket *VideoDecoder::getNextVideoPacket() {
    ESParser *esp = ESParser::getInstance();
    ESPacket *out = esp->getNextPacket();
    if (out->getPacketType() == ESPacket::start_code::video_stream) {
        handleVideoStream(out);
        return getNextVideoPacket();
    }
    return out;
}

void VideoDecoder::loadExtensionUserData(unsigned char i) {
    while (nextVideoPacketIs(ESPacket::start_code::extension) || nextVideoPacketIs(ESPacket::start_code::user_data)) {
        if (i != 1 && nextVideoPacketIs(ESPacket::start_code::extension)) {
            auto *extension_data = (ExtensionPacket *) getNextVideoPacket();
            switch (extension_data->getExtensionType()) {
                case ExtensionPacket::extension_type::sequence_display:
                    loadSequenceDisplayExtension((SequenceDisplayExtensionPacket *) extension_data);
                    break;
                default:
                    throw PacketException("VideoDecoder::loadExtensionUserData: Unhandled Extension Type\n");
            }
        }
        if (nextVideoPacketIs(ESPacket::start_code::user_data)) {
            printf("VideoDecoder::loadExtensionUserData: Unhandled ESPacket with type \"user_data\" was dropped");
        }
    }
}

void VideoDecoder::loadGroupHeaderAndExtension() {
    auto *groupHeader = (GroupOfPicturesHeaderPacket *) getNextVideoPacket();
    pictureDecoder->setClosedGop(groupHeader->isClosedGop());
    pictureDecoder->setBrokenLink(groupHeader->isBrokenLink());
    printf("Decoding new Group of Pictures: Closed? %s, Broken? %s\n", groupHeader->isClosedGop() ? "yes" : "no",
           groupHeader->isBrokenLink() ? "yes" : "no");
}

PictureHeaderPacket::picture_coding_types VideoDecoder::loadPictureHeader() {
    auto *pictureHeader = (PictureHeaderPacket *) getNextVideoPacket();
    pictureDecoder->setPictureCodingType(pictureHeader->getPictureCodingType());
    pictureDecoder->setTemporalReference(pictureHeader->getTemporalReference());
    printf("Decoding new HPicture Header: PictureCodingType = %s, TemporalReference = %hu\n",
           pictureHeader->getPictureCodingTypeString().c_str(),
           pictureHeader->getTemporalReference());
    return pictureHeader->getPictureCodingType();
}

void VideoDecoder::loadPictureCodingExtension() {
    auto *pictureCodingExtension = (PictureCodingExtensionPacket *) getNextVideoPacket();
    printf("Decoding new HPicture Coding Extension: ");
    pictureCodingExtension->print();
    pictureDecoder->setFCode00(pictureCodingExtension->getFCode00());
    pictureDecoder->setFCode01(pictureCodingExtension->getFCode01());
    pictureDecoder->setFCode10(pictureCodingExtension->getFCode10());
    pictureDecoder->setFCode11(pictureCodingExtension->getFCode11());
    pictureDecoder->setIntraDcPrecision(pictureCodingExtension->getIntraDcPrecision());
    pictureDecoder->setPictureStructure(pictureCodingExtension->getPictureStructure());
    pictureDecoder->setTopFieldFirst(pictureCodingExtension->isTopFieldFirst());
    pictureDecoder->setFramePredFrameDct(pictureCodingExtension->isFramePredFrameDct());
    pictureDecoder->setConcealmentMotionVectors(pictureCodingExtension->isConcealmentMotionVectors());
    pictureDecoder->setQScaleType(pictureCodingExtension->isQScaleType());
    pictureDecoder->setIntraVlcFormat(pictureCodingExtension->isIntraVlcFormat());
    pictureDecoder->setAlternateScan(pictureCodingExtension->isAlternateScan());
    pictureDecoder->setRepeatFirstField(pictureCodingExtension->isRepeatFirstField());
    pictureDecoder->setChroma420Type(pictureCodingExtension->isChroma420Type());
    pictureDecoder->setProgressiveFrame(pictureCodingExtension->isProgressiveFrame());
    if (pictureCodingExtension->isCompositeDisplayFlag()) {
        throw VideoException("VideoDecoder::loadPictureCodingExtension: Unhandled feature");
    }
}

void VideoDecoder::handleVideoStream(ESPacket *pPacket) {
    //PESPacket would be handled here but is not currently used by the decoder
}


void VideoDecoder::loadSequenceDisplayExtension(SequenceDisplayExtensionPacket *sdePacket) {
    printf("VideoDecoder: SequenceDisplayExtensionPacket Discarded\n"); // Dropping SequenceDisplayExtensionPacket as it is not used in the decoding process H262 6.3.6
}

PictureDecoder *VideoDecoder::getPictureDecoder() const {
    return pictureDecoder;
}

void VideoDecoder::savePngToFile(HPicture *hPicture, char *destination) {
    cimg_library::CImg<int> *pngPicture = PictureBuilder::makePngFromHPicture(hPicture);
    std::string fileName = destination;//TODO create file before saving to it
    fileName.append("bla.bmp");//TODO print correct filename
    pngPicture->YCbCrtoRGB().save_bmp(fileName.c_str());
    delete pngPicture;
}
