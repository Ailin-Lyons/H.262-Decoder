//
// Created by elnsa on 2020-01-15.
//

#include <RegularStartCodes/SequenceHeaderPacket.h>
#include <RegularStartCodes/SequenceExtensionPacket.h>
#include "VideoDecoder.h"
#include "VideoInformation.h"
#include "../Util/FileInterface.h"
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
    VideoInformation* videoInformation = VideoInformation::getInstance();
    SequenceHeaderPacket *sequence_header = (SequenceHeaderPacket *) getNextVideoPacket();
    sequence_header->print();
    SequenceExtensionPacket *sequence_extension = (SequenceExtensionPacket *) getNextVideoPacket();
    sequence_extension->print();
    ESPacket *extension_user_data = getNextVideoPacket(); //TODO change this to correct packet type
    videoInformation->setHorizontalSize(sequence_header->getHorizontalSizeValue() +
                                       ((unsigned short) (sequence_extension->getHorizontalSizeExtension()) << 12));
    videoInformation->setVerticalSize(sequence_header->getVerticalSizeValue() +
                                     ((unsigned short) (sequence_extension->getVerticalSizeExtension()) << 12));
    std::printf("TODO ExtensionUserData\n");//extension_user_data->print();
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
