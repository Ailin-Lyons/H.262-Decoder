//
// Created by elnsa on 2020-01-19.
//
#include "MotionVectorParser.h"

size_t MotionVectorParser::table_b10_size = 33;
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

size_t MotionVectorParser::table_b11_size = 33;
MotionVectorParser::vlc MotionVectorParser::table_b11[] = {
        {2, -1, 0b11},
        {1, 0,  0b0},
        {2, 1,  0b10}
};

MotionVector *MotionVectorParser::getNextPacket(int r, int s) {
    MotionVector::initializerStruct init = {};
    init.motion_code_r_s_0 = parse_motion_code();
    if (true) {//TODO correct if
    init.motion_residual_r_s_0 = parse_motion_residual();
    }
    if(true){//TODO correct if
        init.dmvector_0 = parse_dmv_code();
    }
    init.motion_code_r_s_1 = parse_motion_code();
    if (true) {//TODO correct if
        init.motion_residual_r_s_1 = parse_motion_residual();
    }
    if(true){//TODO correct if
        init.dmvector_1 = parse_dmv_code();
    }
    return nullptr; //TODO
}

char MotionVectorParser::parse_motion_code() {
    return 0; //TODO
}

char MotionVectorParser::parse_dmv_code() {
    return 0; //TODO
}

unsigned char MotionVectorParser::parse_motion_residual() {
    return 0; //TODO
}

