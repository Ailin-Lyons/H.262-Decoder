//
// Created by elnsa on 2020-01-19.
//
#include "ESParser.h"
#include "CodedBlockPatternParser.h"
#include "../../ESPackets/RegularStartCodes/SequenceExtensionPacket.h"
#include "../../VideoDecoder/VideoInformation.h"


#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

CodedBlockPatternParser::vlc CodedBlockPatternParser::table_b9[] = {{3, 60, 0b111},
                                                                    {4, 4,  0b1101},
                                                                    {4, 8,  0b1100},
                                                                    {4, 16, 0b1011},
                                                                    {4, 32, 0b1010},
                                                                    {5, 12, 0b10011},
                                                                    {5, 48, 0b10010},
                                                                    {5, 20, 0b10001},
                                                                    {5, 40, 0b10000},
                                                                    {5, 28, 0b01111},
                                                                    {5, 44, 0b01110},
                                                                    {5, 52, 0b01101},
                                                                    {5, 56, 0b01100},
                                                                    {5, 1,  0b01011},
                                                                    {5, 61, 0b01010},
                                                                    {5, 2,  0b01001},
                                                                    {5, 62, 0b01000},
                                                                    {6, 24, 0b001111},
                                                                    {6, 36, 0b001110},
                                                                    {6, 3,  0b001101},
                                                                    {6, 63, 0b001100},
                                                                    {7, 5,  0b0010111},
                                                                    {7, 9,  0b0010110},
                                                                    {7, 17, 0b0010101},
                                                                    {7, 33, 0b0010100},
                                                                    {7, 6,  0b0010011},
                                                                    {7, 10, 0b0010010},
                                                                    {7, 18, 0b0010001},
                                                                    {7, 34, 0b0010000},
                                                                    {8, 7,  0b00011111},
                                                                    {8, 11, 0b00011110},
                                                                    {8, 19, 0b00011101},
                                                                    {8, 35, 0b00011100},
                                                                    {8, 13, 0b00011011},
                                                                    {8, 49, 0b00011010},
                                                                    {8, 21, 0b00011001},
                                                                    {8, 41, 0b00011000},
                                                                    {8, 14, 0b00010111},
                                                                    {8, 50, 0b00010110},
                                                                    {8, 22, 0b00010101},
                                                                    {8, 42, 0b00010100},
                                                                    {8, 15, 0b00010011},
                                                                    {8, 51, 0b00010010},
                                                                    {8, 23, 0b00010001},
                                                                    {8, 43, 0b00010000},
                                                                    {8, 25, 0b00001111},
                                                                    {8, 37, 0b00001110},
                                                                    {8, 26, 0b00001101},
                                                                    {8, 38, 0b00001100},
                                                                    {8, 29, 0b00001011},
                                                                    {8, 45, 0b00001010},
                                                                    {8, 53, 0b00001001},
                                                                    {8, 57, 0b00001000},
                                                                    {8, 30, 0b00000111},
                                                                    {8, 46, 0b00000110},
                                                                    {8, 54, 0b00000101},
                                                                    {8, 58, 0b00000100},
                                                                    {9, 31, 0b000000111},
                                                                    {9, 47, 0b000000110},
                                                                    {9, 55, 0b000000101},
                                                                    {9, 59, 0b000000100},
                                                                    {9, 27, 0b000000011},
                                                                    {9, 39, 0b000000010},
                                                                    {9, 0,  0b000000001}};

CodedBlockPattern *CodedBlockPatternParser::coded_block_pattern(CodedBlockPattern **out) {
    CodedBlockPattern::initializerStruct init = {};
    init.coded_block_pattern_420 = getCodedBlockPattern();
    if (VideoInformation::getInstance()->getChromaFormat() == SequenceExtensionPacket::chroma_format_type::cf_422) {
        init.coded_block_pattern_1 = read(2);
    }
    if (VideoInformation::getInstance()->getChromaFormat() == SequenceExtensionPacket::chroma_format_type::cf_444) {
        init.coded_block_pattern_2 = read(6);
    }
    return new CodedBlockPattern(init);
}

unsigned char CodedBlockPatternParser::getCodedBlockPattern() {
    for (vlc code: table_b9) {
        if (peek(code.numbits) == code.key) {
            read(code.numbits);
            return code.value;
        }
    }
    throw PacketException("CodedBlockPatternParser::getCodedBlockPattern: Unexpected value\n");
}
