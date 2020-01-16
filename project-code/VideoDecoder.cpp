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
    ESParser *esp = ESParser::getInstance();
    FileInterface* fi = FileInterface::getInstance();
    while (fi->hasNextPacket()) {
        ESPacket *pack = esp->getNextPacket();
        if (pack != nullptr) {
            pack->print();
        }
        free(pack);
    }
}

bool VideoDecoder::loadFile(char *relative_path) {
    try {
        FileInterface::getInstance()->setInstance(relative_path);
        ESParser *esp = ESParser::getInstance();
        esp->initiateStream();
        return true;
    } catch (const FileException) {
        std::printf("Error loading file!");
        return false;
    }
}

VideoDecoder::VideoDecoder() {
    //TODO?
}

void VideoDecoder::loadVideoSequence() {
    ESParser *esp = ESParser::getInstance();
    esp->next_start_code();
    while (ESPacket::getStartCode(esp->nextESPacketID()) != ESPacket::start_code::sequence_header) {
        ESPacket* pack = esp->getNextPacket();
        if (pack != nullptr) { //temp remove this
            std::printf("VideoDecoder::loadVideoSequence TODO handle PESPacket: %x %x\n",pack->getStreamId(),pack->getStreamId()); //pack->print();
        }
    }

    SequenceHeaderPacket* sequence_header = (SequenceHeaderPacket*) esp->getNextPacket();
    sequence_header->print();
    if ( ESPacket::getStartCode(esp->nextESPacketID()) == ESPacket::start_code::extension ) {
        SequenceExtensionPacket* sequence_extension = (SequenceExtensionPacket*) esp->getNextPacket();
        sequence_extension->print();
        SequenceExtensionPacket* extension_user_data = (SequenceExtensionPacket*) esp->getNextPacket(); //TODO change this to correct packet type
        std::printf("TODO");//extension_user_data->print();
    }else{
        throw PacketException("This stream is not H262");
    }
}
