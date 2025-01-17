#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-bool-literals"
//
// Created by elnsa on 2020-01-19.
//
#include "MotionVectorParser.h"
#include "../../PictureDecoder/PictureDecoder.h"
#include "../../VideoDecoder/VideoDecoder.h"

MotionVectorParser::vlc MotionVectorParser::table_b10[] = {
        {11, -16, 0b00000011001},
        {11, -15, 0b00000011011},
        {11, -14, 0b00000011101},
        {11, -13, 0b00000011111},
        {11, -12, 0b00000100001},
        {11, -11, 0b00000100011},
        {10, -10, 0b0000010011},
        {10, -9,  0b0000010101},
        {10, -8,  0b0000010111},
        {8,  -7,  0b00000111},
        {8,  -6,  0b00001001},
        {8,  -5,  0b00001011},
        {7,  -4,  0b0000111},
        {5,  -3,  0b00011},
        {4,  -2,  0b0011},
        {3,  -1,  0b011},
        {1,  0,   0b1},
        {3,  1,   0b010},
        {4,  2,   0b0010},
        {5,  3,   0b00010},
        {7,  4,   0b0000110},
        {8,  5,   0b00001010},
        {8,  6,   0b00001000},
        {8,  7,   0b00000110},
        {10, 8,   0b0000010110},
        {10, 9,   0b0000010100},
        {10, 10,  0b0000010010},
        {11, 11,  0b00000100010},
        {11, 12,  0b00000100000},
        {11, 13,  0b00000011110},
        {11, 14,  0b00000011100},
        {11, 15,  0b00000011010},
        {11, 16,  0b00000011000}
};

MotionVectorParser::vlc MotionVectorParser::table_b11[] = {
        {2, -1, 0b11},
        {1, 0,  0b0},
        {2, 1,  0b10}
};

MotionVector *MotionVectorParser::getNextPacket(bool r, bool s) {
    MotionVector::initializerStruct init = {0, 0, 0, 0, 0, 0};
    init.r = r;
    init.s = s;
    init.motion_code_r_s_0 = parse_motion_code();
    if ((VideoDecoder::getInstance()->getPictureDecoder()->getFCodeST(s, false) != 1) &&
        (init.motion_code_r_s_0 != 0)) {
        init.motion_residual_r_s_0 = parse_motion_residual(s, 0);
    }
    if (parse_dmv()) {
        init.dmvector_0 = parse_dmvector();
    }
    init.motion_code_r_s_1 = parse_motion_code();
    if ((VideoDecoder::getInstance()->getPictureDecoder()->getFCodeST(s, true) != 1) && (init.motion_code_r_s_1 != 0)) {
        init.motion_residual_r_s_1 = parse_motion_residual(s, 1);
    }
    if (parse_dmv()) {
        init.dmvector_1 = parse_dmvector();
    }
    return new MotionVector(init);
}

char MotionVectorParser::parse_motion_code() {
    for (vlc code: table_b10) {
        if (peek(code.numbits) == code.key) {
            READ(code.numbits);
            return code.value;
        }
    }
    throw PacketException("MotionVectorParser::parse_motion_code: Unexpected Value");
}

bool MotionVectorParser::parse_dmv() {
    PictureDecoder *pictureDecoder = VideoDecoder::getInstance()->getPictureDecoder();
    return (pictureDecoder->getFrameMotionType() == 0b11) || (pictureDecoder->getFieldMotionType() == 0b11);
}

unsigned char MotionVectorParser::parse_motion_residual(bool s, bool t) {
    return (unsigned char) READ((unsigned int) (VideoDecoder::getInstance()->getPictureDecoder()->getFCodeST(s, t) - 1));
}

char MotionVectorParser::parse_dmvector() {
    for (vlc code: table_b11) {
        if (peek(code.numbits) == code.key) {
            READ(code.numbits);
            return code.value;
        }
    }
    throw PacketException("MotionVectorParser::parse_dmvector: Unexpected value\n");
}


#pragma clang diagnostic pop