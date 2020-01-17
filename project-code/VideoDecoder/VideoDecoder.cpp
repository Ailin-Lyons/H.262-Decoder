//
// Created by elnsa on 2020-01-15.
//

#include <RegularStartCodes/SequenceHeaderPacket.h>
#include <RegularStartCodes/SequenceExtensionPacket.h>
#include "VideoDecoder.h"
#include "VideoInformation.h"
#include "../Util/FileInterface.h"
#include "../Util/FileException.cpp"
#include "../PacketParsers/ESParser.h"

VideoDecoder *VideoDecoder::instance = nullptr;

void VideoDecoder::decodeToFile(char *source, char *destination) {
    std::printf("\n***Loading file: %s ***\n", source);
    loadFile(source);
    std::printf("***Loading file... Done!***\n", source);
    std::printf("\n***Loading video_sequence...***\n");
    loadVideoSequence();
    std::printf("\n***Loading video_sequence...Done!***\n\n");
    FileInterface *fi = FileInterface::getInstance();
    while (fi->hasNextPacket()) {
        ESPacket *pack = getNextVideoPacket();
        //if(pack!= nullptr) getNextVideoPacket()->print();
    }
}

bool VideoDecoder::loadFile(char *relative_path) {
    try {
        FileInterface::getInstance()->setInstance(relative_path);
        ESParser *esp = ESParser::getInstance();
        esp->initiateStream();
        return true;
    } catch (const FileException) {
        std::printf("Error loading file!\n");
        return false;
    }
}

VideoDecoder::VideoDecoder() {
}

void VideoDecoder::loadVideoSequence() {
    VideoInformation *videoInfo = VideoInformation::getInstance();
    SequenceHeaderPacket *seq_hed = (SequenceHeaderPacket *) getNextVideoPacket();
    seq_hed->print();
    SequenceExtensionPacket *seq_ex = (SequenceExtensionPacket *) getNextVideoPacket();
    seq_ex->print();
    ESPacket *extension_user_data = getNextVideoPacket(); //TODO change this to correct packet type
    videoInfo->setHorizontalSize(seq_hed->getHVal() + (seq_ex->getHExt() << 12));
    videoInfo->setVerticalSize(seq_hed->getVVal() + (seq_ex->getVExt() << 12));
    videoInfo->setAspectRatio(seq_hed->getAspectRatioInformation());
    videoInfo->setFrameRate(seq_hed->getFrameRate(),seq_ex->getFrameExtN(),seq_ex->getFrameExtD());
    videoInfo->setBitRate((seq_ex->getBitRateExt() << 12) + seq_hed->getBitRateVal());
    videoInfo->setVBVBufSize((seq_ex->getVBVBufVal() << 10) + seq_hed->getVBVBufVal());
    if(seq_hed->getCPFlag()) throw PacketException("VideoDecoder::loadVideoSequence: Unhandled coding standard"); //This bit shall be '0' in H.262
    //TODO load quant matrix here? H262 6.3.3, 6.3.11
    videoInfo->setProfileLevel(seq_ex->getProfileAndLevelIndication());
    videoInfo->setProgressiveSequence(seq_ex->getProgSeq());
    videoInfo->setChromaFormat(seq_ex->getChromaFormat());
    videoInfo->setLowDelay(seq_ex->getLowDelay());
    //TODO continue here by parsing any fields from extension_user_data
}

ESPacket *VideoDecoder::getNextVideoPacket() {
    ESParser *esp = ESParser::getInstance();
    ESPacket *out = esp->getNextPacket();
    if (out == nullptr) {
        std::printf("TODO handle this packet");
        return out;
    }
    if (out->getPacketType() == ESPacket::start_code::video_stream) {
        //TODO handle video stream
        std::printf("VideoDecoder::loadVideoSequence TODO handle E0 PESPacket\n");
        return getNextVideoPacket();
    } else if (out->getPacketType() == ESPacket::start_code::sequence_header ||
               out->getPacketType() == ESPacket::start_code::extension ||
               out->getPacketType() == ESPacket::start_code::user_data ||
               out->getPacketType() == ESPacket::start_code::group ||
               out->getPacketType() == ESPacket::start_code::picture ||
               out->getPacketType() == ESPacket::start_code::slice) {
        return out;
    } else {
        throw PacketException("VideoDecoder::getNextVideoPacket unexpected start_code\n");
    }
}
