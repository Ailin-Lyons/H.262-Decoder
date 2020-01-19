//
// Created by elnsa on 2020-01-15.
//

#include <RegularStartCodes/SequenceHeaderPacket.h>
#include <RegularStartCodes/SequenceExtensionPacket.h>
#include <RegularStartCodes/GroupOfPicturesHeaderPacket.h>
#include <RegularStartCodes/SequenceDisplayExtensionPacket.h>
#include "VideoDecoder.h"
#include "VideoInformation.h"
#include "VideoException.cpp"
#include "../Util/FileInterface.h"
#include "../Util/FileException.cpp"
#include "../PacketParsers/ESParser.h"
#include "../PictureDecoder/PictureDecoder.h"

VideoDecoder *VideoDecoder::instance = nullptr;

VideoDecoder::VideoDecoder() {
}

void VideoDecoder::decodeToFile(char *source, char *destination) {
    pictureDecoder = new PictureDecoder();
    loadFile(source);
    printf("\n***Loading video_sequence...***\n");
    loadVideoSequence();
    printf("\n***Loading video_sequence...Done!***\n");
    printf("\n***Beginning Decoding process...***\n");
    do {
        loadExtensionUserData(0);
        do {
            makePicture();
        } while (nextVideoPacketIs(ESPacket::start_code::picture) || nextVideoPacketIs(ESPacket::start_code::group));
        if (!nextVideoPacketIs(ESPacket::start_code::sequence_end)) {
            loadVideoSequence();
        }
    } while (!nextVideoPacketIs(ESPacket::start_code::sequence_end));
    printf("\n***Decoding process done...***\n");
}

bool VideoDecoder::loadFile(char *relative_path) {
    printf("\n***Loading file: %s ***\n", relative_path);
    try {
        FileInterface::getInstance()->setInstance(relative_path);
        ESParser *esp = ESParser::getInstance();
        esp->initiateStream();
        printf("***Loading file... Done!***\n", relative_path);
        return true;
    } catch (const FileException) {
        printf("Error loading file!\n");
        return false;
    }
}

void VideoDecoder::loadVideoSequence() {
    printf("\n   ...Updating Video Information...\n");
    VideoInformation *videoInfo = VideoInformation::getInstance();
    SequenceHeaderPacket *seq_hed = (SequenceHeaderPacket *) getNextVideoPacket();
    if (!nextVideoPacketIs(ESPacket::start_code::extension)) {
        throw VideoException("VideoDecoder::loadVideoSequence: Unhandled coding standard");
    }
    SequenceExtensionPacket *seq_ex = (SequenceExtensionPacket *) getNextVideoPacket();
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

void VideoDecoder::makePicture() {
    if (nextVideoPacketIs(ESPacket::start_code::group)) {
        loadGroupHeaderAndExtension();
        loadExtensionUserData(1);
    }
    loadPictureHeader();
    loadPictureCodingExtension();
    loadExtensionUserData(2);
    loadPictureData();
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
            ExtensionPacket *extension_data = (ExtensionPacket *) getNextVideoPacket();
            switch(extension_data->getExtensionType()){
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
    GroupOfPicturesHeaderPacket *groupHeader = (GroupOfPicturesHeaderPacket *) getNextVideoPacket();
    pictureDecoder->setClosedGop(groupHeader->isClosedGop());
    pictureDecoder->setBrokenLink(groupHeader->isBrokenLink());
    printf("Decoding new Group of Pictures: Closed? %s, Broken? %s\n", groupHeader->isClosedGop() ? "yes" : "no",
           groupHeader->isBrokenLink() ? "yes" : "no");
}

void VideoDecoder::loadPictureHeader() {
    ESPacket *pictureHeader = getNextVideoPacket(); //TODO handle the loaded packet
    printf("TODO loadPictureHeader\n");
}

void VideoDecoder::loadPictureCodingExtension() {
    ESPacket *pictureCodingExtension = getNextVideoPacket(); //TODO handle the loaded packet
    printf("TODO loadPictureCodingExtension\n");
}

void VideoDecoder::loadPictureData() {
    do {
        ESPacket *pictureData = getNextVideoPacket(); //TODO handle the loaded packet
        printf("TODO loadPictureData: slice with ID %x\n", pictureData->getStreamId());
    } while (nextVideoPacketIs(ESPacket::start_code::slice));
}

void VideoDecoder::handleVideoStream(ESPacket *pPacket) {//TODO handle the loaded packet
    printf("TODO handleVideoStream\n");
}

void VideoDecoder::loadSequenceDisplayExtension(SequenceDisplayExtensionPacket *sdePacket) {
    // Dropping SequenceDisplayExtensionPacket as it is not used in the decoding process H262 6.3.6
}
