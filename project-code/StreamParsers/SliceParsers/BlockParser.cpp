//
// Created by elnsa on 2020-01-19.
//

#include "../../PictureDecoder/PictureDecoder.h"
#include "../../VideoDecoder/VideoDecoder.h"
#include "../../VideoDecoder/VideoInformation.h"
#include "BlockParser.h"

BlockParser::vlc BlockParser::table_b12[] = {{3, 0,  0b100},
                                             {2, 1,  0b00},
                                             {2, 2,  0b01},
                                             {3, 3,  0b101},
                                             {3, 4,  0b110},
                                             {4, 5,  0b1110},
                                             {5, 6,  0b11110},
                                             {6, 7,  0b111110},
                                             {7, 8,  0b1111110},
                                             {8, 9,  0b11111110},
                                             {9, 10, 0b111111110},
                                             {9, 11, 0b111111111}};
BlockParser::vlc BlockParser::table_b13[] = {{2,  0,  0b00},
                                             {2,  1,  0b01},
                                             {2,  2,  0b10},
                                             {3,  3,  0b110},
                                             {4,  4,  0b1110},
                                             {5,  5,  0b11110},
                                             {6,  6,  0b111110},
                                             {7,  7,  0b1111110},
                                             {8,  8,  0b11111110},
                                             {9,  9,  0b111111110},
                                             {10, 10, 0b1111111110},
                                             {10, 11, 0b1111111111}};

Block *BlockParser::block(size_t i) {
    PictureDecoder *pictureDecoder = VideoDecoder::getInstance()->getPictureDecoder();
    Block::initializerStruct init = {};
    bool pattern_code[12];
    initializePatternCode(pattern_code);
    init.cc = getCC(i);
    if (pattern_code[i]) {
        if (pictureDecoder->isMacroblockIntra()) {
            init.dct_dc_size = getDctDcSize(init.cc);
            if (init.dct_dc_size != 0) {
                init.dct_dc_differential = read(init.dct_dc_size);
            }
        } else {
            //First DCT coefficient
        }
        //while(nextbits()!= End of block)
        //  Subsequent DCT coefficients
        //End of block
    }
    return new Block(init);
}

unsigned char BlockParser::getDctDcSizeLuminance() {
    for (vlc code: table_b12) {
        if (peek(code.numbits) == code.key) {
            read(code.numbits);
            return code.value;
        }
    }
    throw PacketException("BlockParser::getDctDcSizeLuminance: Unexpected value\n");
}

unsigned char BlockParser::getDctDcSizeChrominance() {
    for (vlc code: table_b13) {
        if (peek(code.numbits) == code.key) {
            read(code.numbits);
            return code.value;
        }
    }
    throw PacketException("BlockParser::getDctDcSizeChrominance: Unexpected value\n");
}

void BlockParser::initializePatternCode(bool *pattern_code) {
    PictureDecoder *pictureDecoder = VideoDecoder::getInstance()->getPictureDecoder();
    for (int i = 0; i < 12; i++) {
        pattern_code[i] = pictureDecoder->isMacroblockIntra();
    }
    if (pictureDecoder->isMacroblockPattern()) {
        for (int i = 0; i < 6; i++) {
            if (pictureDecoder->getCbp() & (1 << (5 - i))) pattern_code[i] = 1;
        }
        if (VideoInformation::getInstance()->getChromaFormat() ==
            SequenceExtensionPacket::chroma_format_type::cf_422) {
            for (int i = 6; i < 8; i++) {
                if (pictureDecoder->getCodedBlockPattern1() & (1 << (7 - i))) pattern_code[i] = 1;
            }
        }
        if (VideoInformation::getInstance()->getChromaFormat() ==
            SequenceExtensionPacket::chroma_format_type::cf_444) {
            for (int i = 6; i < 12; i++) {
                if (pictureDecoder->getCodedBlockPattern2() & (1 << (11 - i))) pattern_code[i] = 1;
            }
        }
    }
}

unsigned char BlockParser::getCC(size_t i) {
    if (i < 4) {
        return 0;
    }
    else {
        return i % 2 + 1;
    }
}

unsigned char BlockParser::getDctDcSize(unsigned char cc) {
    if (cc == 0) {
        return getDctDcSizeLuminance();
    } else {
        return getDctDcSizeChrominance();
    }
}

