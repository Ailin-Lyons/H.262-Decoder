//
// Created by elnsa on 2020-01-15.
//

#include <RegularStartCodes/SequenceHeaderPacket.h>
#include <RegularStartCodes/SequenceExtensionPacket.h>
#include "VideoDecoder.h"
#include "VideoInformation.h"
#include "VideoException.cpp"
#include "../Util/FileInterface.h"
#include "../Util/FileException.cpp"
#include "../PacketParsers/ESParser.h"

VideoDecoder *VideoDecoder::instance = nullptr;

void VideoDecoder::decodeToFile(char *source, char *destination) {
    loadFile(source);
    std::printf("\n***Loading video_sequence...***\n");
    loadVideoSequence();
    std::printf("\n***Loading video_sequence...Done!***\n");
    std::printf("\n***Beginning Decoding process...***\n");
    do {
        loadExtensionUserData(0);
        do {
            makePicture();
        } while (isNextVideoPacket(ESPacket::start_code::picture) || isNextVideoPacket(ESPacket::start_code::group));
        if (!isNextVideoPacket(ESPacket::start_code::sequence_end)) {
            loadVideoSequence();
        }
    } while (!isNextVideoPacket(ESPacket::start_code::sequence_end));
    std::printf("\n***Decoding process done...***\n");
}

bool VideoDecoder::loadFile(char *relative_path) {
    std::printf("\n***Loading file: %s ***\n", relative_path);
    try {
        FileInterface::getInstance()->setInstance(relative_path);
        ESParser *esp = ESParser::getInstance();
        esp->initiateStream();
        std::printf("***Loading file... Done!***\n", relative_path);
        return true;
    } catch (const FileException) {
        std::printf("Error loading file!\n");
        return false;
    }
}

VideoDecoder::VideoDecoder() {
}

void VideoDecoder::loadVideoSequence() {
    std::printf("\n***Updating Video Information...***\n");
    VideoInformation *videoInfo = VideoInformation::getInstance();
    SequenceHeaderPacket *seq_hed = (SequenceHeaderPacket *) getNextVideoPacket();
    seq_hed->print();
    if (!isNextVideoPacket(ESPacket::start_code::extension)) {
        throw VideoException("VideoDecoder::loadVideoSequence: Unhandled coding standard");
    }
    SequenceExtensionPacket *seq_ex = (SequenceExtensionPacket *) getNextVideoPacket();
    seq_ex->print();
    videoInfo->setHorizontalSize(seq_hed->getHVal() + (seq_ex->getHExt() << 12));
    videoInfo->setVerticalSize(seq_hed->getVVal() + (seq_ex->getVExt() << 12));
    videoInfo->setAspectRatio(seq_hed->getAspectRatioInformation());
    videoInfo->setFrameRate(seq_hed->getFrameRate(), seq_ex->getFrameExtN(), seq_ex->getFrameExtD());
    videoInfo->setBitRate((seq_ex->getBitRateExt() << 12) + seq_hed->getBitRateVal());
    videoInfo->setVBVBufSize((seq_ex->getVBVBufVal() << 10) + seq_hed->getVBVBufVal());
    if (seq_hed->getCPFlag())
        throw PacketException(
                "VideoDecoder::loadVideoSequence: Unhandled coding standard"); //This bit shall be '0' in H.262
    //TODO load quant matrix here? H262 6.3.3, 6.3.11
    videoInfo->setProfileLevel(seq_ex->getProfileAndLevelIndication());
    videoInfo->setProgressiveSequence(seq_ex->getProgSeq());
    videoInfo->setChromaFormat(seq_ex->getChromaFormat());
    videoInfo->setLowDelay(seq_ex->getLowDelay());
}

ESPacket *VideoDecoder::getNextVideoPacket() {
    ESParser *esp = ESParser::getInstance();
    ESPacket *out = esp->getNextPacket();
    if (out == nullptr) {
        std::printf("TODO handle this packet");
        return out;
    }
    if (out->getPacketType() == ESPacket::start_code::video_stream) {
        handleVideoStream(out);
        return getNextVideoPacket();
    }
    return out;
}

void VideoDecoder::loadExtensionUserData(unsigned char i) {    //TODO handle the loaded packets
    while (isNextVideoPacket(ESPacket::start_code::extension) || isNextVideoPacket(ESPacket::start_code::user_data)) {
        if (i != 1 && isNextVideoPacket(ESPacket::start_code::extension)) {
            ESPacket *extension_data = getNextVideoPacket();
        }
        if (isNextVideoPacket(ESPacket::start_code::user_data)) {
            ESPacket *user_data = getNextVideoPacket();
        }
    }
}

bool VideoDecoder::isNextVideoPacket(ESPacket::start_code startCode) {
    if (ESPacket::getStartCode(ESParser::getInstance()->nextESPacketID()) == ESPacket::start_code::video_stream) {
        handleVideoStream(ESParser::getInstance()->getNextPacket());
        return isNextVideoPacket(startCode);
    }
    return ESPacket::getStartCode(ESParser::getInstance()->nextESPacketID()) == startCode;
}

void VideoDecoder::loadGroupHeaderAndExtension() {//TODO handle the loaded packet
    ESPacket *groupHeader = getNextVideoPacket();
}

void VideoDecoder::loadPictureHeader() {
    ESPacket *pictureHeader = getNextVideoPacket(); //TODO handle the loaded packet

}

void VideoDecoder::loadPictureCodingExtension() {
    ESPacket *pictureCodingExtension = getNextVideoPacket(); //TODO handle the loaded packet
}

void VideoDecoder::loadPictureData() {
    do {
        ESPacket *pictureData = getNextVideoPacket(); //TODO handle the loaded packet
    } while (isNextVideoPacket(ESPacket::start_code::slice));
}

void VideoDecoder::handleVideoStream(ESPacket *pPacket) {//TODO handle the loaded packet

}

void VideoDecoder::makePicture() {
    if (isNextVideoPacket(ESPacket::start_code::group)) {
        loadGroupHeaderAndExtension();
        loadExtensionUserData(1);
    }
    loadPictureHeader();
    loadPictureCodingExtension();
    loadExtensionUserData(2);
    loadPictureData();
}
