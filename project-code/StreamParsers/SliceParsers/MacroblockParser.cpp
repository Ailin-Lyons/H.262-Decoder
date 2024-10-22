//
// Created by elnsa on 2020-01-19.
//
#include "ESParser.h"
#include "../../PictureDecoder/Slice/Macroblock.h"
#include "MacroblockParser.h"
#include "MotionVectorsParser.cpp"
#include "CodedBlockPatternParser.h"
#include "BlockParser.h"
#include "../../VideoDecoder/VideoInformation.h"


#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

MacroblockParser::vlc MacroblockParser::table_b1[] = {{1,  1,  0b1}, //Excludes macroblock_escape as that is handled separately
                                                      {3,  2,  0b011},
                                                      {3,  3,  0b010},
                                                      {4,  4,  0b0011},
                                                      {4,  5,  0b0010},
                                                      {5,  6,  0b00011},
                                                      {5,  7,  0b00010},
                                                      {7,  8,  0b0000111},
                                                      {7,  9,  0b0000110},
                                                      {8,  10, 0b00001011},
                                                      {8,  11, 0b00001010},
                                                      {8,  12, 0b00001001},
                                                      {8,  13, 0b00001000},
                                                      {8,  14, 0b00000111},
                                                      {8,  15, 0b00000110},
                                                      {10, 16, 0b0000010111},
                                                      {10, 17, 0b0000010110},
                                                      {10, 18, 0b0000010101},
                                                      {10, 19, 0b0000010100},
                                                      {10, 20, 0b0000010011},
                                                      {10, 21, 0b0000010010},
                                                      {11, 22, 0b00000100011},
                                                      {11, 23, 0b00000100010},
                                                      {11, 24, 0b00000100001},
                                                      {11, 25, 0b00000100000},
                                                      {11, 26, 0b00000011111},
                                                      {11, 27, 0b00000011110},
                                                      {11, 28, 0b00000011101},
                                                      {11, 29, 0b00000011100},
                                                      {11, 30, 0b00000011011},
                                                      {11, 31, 0b00000011010},
                                                      {11, 32, 0b00000011001},
                                                      {11, 33, 0b00000011000}};

Macroblock *MacroblockParser::getNextPacket(unsigned char qsc) {
    PictureDecoder *pictureDecoder = VideoDecoder::getInstance()->getPictureDecoder();
    Macroblock::initializerStruct init = {};
    init.macroblock_address_increment = getAddressIncrement();
    init.macroBlockModes = MacroblockModesParser::macroblock_modes();
    pictureDecoder->updateMacroBlockModes(init.macroBlockModes, init.macroblock_address_increment);
    if (init.macroBlockModes->isMacroblockQuant()) {
        init.quantiser_scale_code = (unsigned char) read(5);
    } else {
        init.quantiser_scale_code = qsc;
    }
    if (init.macroBlockModes->isMacroblockMotionForward() || (init.macroBlockModes->isMacroblockIntra() &&
                                                              pictureDecoder->isConcealmentMotionVectors())) {
        init.forwardMotionVectors = MotionVectorsParser::motion_vectors(0); // NOLINT(modernize-use-bool-literals)
    }
    if (init.macroBlockModes->isMacroblockMotionBackward()) {
        init.backwardMotionVectors = MotionVectorsParser::motion_vectors(1); // NOLINT(modernize-use-bool-literals)
    }
    if (init.macroBlockModes->isMacroblockIntra() && pictureDecoder->isConcealmentMotionVectors()) {
        read(1);//marker bit
    }
    if (init.macroBlockModes->isMacroblockPattern()) {
        init.codedBlockPattern = CodedBlockPatternParser::coded_block_pattern();
        pictureDecoder->updateCodedBlockPattern(init.codedBlockPattern);
    }
    init.block_count = getBlockCount(VideoInformation::getInstance()->getChromaFormat());
    init.blocks = (Block **) calloc(init.block_count, sizeof(void *));
    for (size_t i = 0; i < init.block_count; i++) {
        BlockParser::block(i, &init.blocks[i]);
    }
    return new Macroblock(init);
}

size_t MacroblockParser::getAddressIncrement() {
    size_t out = 0;
    while (peek(11) == 0b00000001000) { //handle macroblock_escape
        read(11);
        out += 33;
    }
    for (vlc code: table_b1) {
        if (peek(code.numBits) == code.key) {
            read(code.numBits);
            return out + code.value;
        }
    }
    throw PacketException("MacroblockParser::getAddressIncrement: Unexpected value\n");
}

unsigned char MacroblockParser::getBlockCount(SequenceExtensionPacket::chroma_format_type type) {
    switch (type) {
        case SequenceExtensionPacket::chroma_format_type::cf_420:
            return 6;
        case SequenceExtensionPacket::chroma_format_type::cf_422:
            return 8;
        case SequenceExtensionPacket::chroma_format_type::cf_444:
            return 12;
        default:
            throw PacketException("MacroblockParser::getBlockCount: Unexpected type");
    }
}


