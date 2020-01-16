//
// Created by elnsa on 2020-01-15.
//

#include <RegularStartCodes/SequenceHeaderPacket.h>
#include <RegularStartCodes/SequenceExtensionPacket.h>
#include "VideoDecoder.h"

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
        getNextVideoPacket()->print();
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
    //TODO?
}

void VideoDecoder::loadVideoSequence() {
    ESParser *esp = ESParser::getInstance();
    next_start_code = ESPacket::start_code::sequence_header;
    SequenceHeaderPacket *sequence_header = (SequenceHeaderPacket *) getNextVideoPacket();
    sequence_header->print();
    next_start_code = ESPacket::start_code::extension;
    SequenceExtensionPacket *sequence_extension = (SequenceExtensionPacket *) getNextVideoPacket();
    sequence_extension->print();
    // SequenceExtensionPacket* extension_user_data = (SequenceExtensionPacket*) getNextVideoPacket(); //TODO change this to correct packet type
    std::printf("TODO ExtensionUserData\n");//extension_user_data->print();
}

ESPacket *VideoDecoder::getNextVideoPacket() {
    ESParser *esp = ESParser::getInstance();
    ESPacket *out = esp->getNextPacket();
    if (out == nullptr) {
        return getNextVideoPacket(); //TODO Remove this if clause. It is a bypass while some packets arent implemented
    }
    if (out->getPacketType() == ESPacket::start_code::picture ||
        out->getPacketType() == ESPacket::start_code::slice ||
        out->getPacketType() == ESPacket::start_code::group ||
        out->getPacketType() == ESPacket::start_code::sequence_header) {
        return out; //TODO remove this?
    }
    if (out->getPacketType() == next_start_code) {
        return out;
    } else if (out->getPacketType() == ESPacket::start_code::video_stream) {
        //TODO handle video stream
        std::printf("VideoDecoder::loadVideoSequence TODO handle E0 PESPacket\n");
        return getNextVideoPacket();
    } else {
        throw PacketException("VideoDecoder::getNextVideoPacket unexpected start_code\n");
    }
}
