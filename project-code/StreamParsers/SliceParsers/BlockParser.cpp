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

BlockParser::vlc_signed BlockParser::table_b14[] = {{0b11,               0,  1,  2},
                                                    {0b011,              1,  1,  3},
                                                    {0b0100,             0,  2,  4},
                                                    {0b0101,             2,  1,  4},
                                                    {0b00101,            0,  3,  5},
                                                    {0b00111,            3,  1,  5},
                                                    {0b00110,            4,  1,  5},
                                                    {0b000110,           1,  2,  6},
                                                    {0b000111,           5,  1,  6},
                                                    {0b000101,           6,  1,  6},
                                                    {0b000100,           7,  1,  6},
                                                    {0b0000110,          0,  4,  7},
                                                    {0b0000100,          2,  2,  7},
                                                    {0b0000111,          8,  1,  7},
                                                    {0b0000101,          9,  1,  7},
                                                    {0b00100110,         0,  5,  8},
                                                    {0b00100001,         0,  6,  8},
                                                    {0b00100101,         1,  3,  8},
                                                    {0b00100100,         3,  2,  8},
                                                    {0b00100111,         10, 1,  8},
                                                    {0b00100011,         11, 1,  8},
                                                    {0b00100010,         12, 1,  8},
                                                    {0b00100000,         13, 1,  8},
                                                    {0b0000001010,       0,  7,  10},
                                                    {0b0000001100,       1,  4,  10},
                                                    {0b0000001011,       2,  3,  10},
                                                    {0b0000001111,       4,  2,  10},
                                                    {0b0000001001,       5,  2,  10},
                                                    {0b0000001110,       14, 1,  10},
                                                    {0b0000001101,       15, 1,  10},
                                                    {0b0000001000,       16, 1,  10},
                                                    {0b000000011101,     0,  8,  12},
                                                    {0b000000011000,     0,  9,  12},
                                                    {0b000000010011,     0,  10, 12},
                                                    {0b000000010000,     0,  11, 12},
                                                    {0b000000011011,     1,  5,  12},
                                                    {0b000000010100,     2,  4,  12},
                                                    {0b000000011100,     3,  3,  12},
                                                    {0b000000010010,     4,  3,  12},
                                                    {0b000000011110,     6,  2,  12},
                                                    {0b000000010101,     7,  2,  12},
                                                    {0b000000010001,     8,  2,  12},
                                                    {0b000000011111,     17, 1,  12},
                                                    {0b000000011010,     18, 1,  12},
                                                    {0b000000011001,     19, 1,  12},
                                                    {0b000000010111,     20, 1,  12},
                                                    {0b000000010110,     21, 1,  12},
                                                    {0b0000000011010,    0,  12, 13},
                                                    {0b0000000011001,    0,  13, 13},
                                                    {0b0000000011000,    0,  14, 13},
                                                    {0b0000000010111,    0,  15, 13},
                                                    {0b0000000010110,    1,  6,  13},
                                                    {0b0000000010101,    1,  7,  13},
                                                    {0b0000000010100,    2,  5,  13},
                                                    {0b0000000010011,    3,  4,  13},
                                                    {0b0000000010010,    5,  3,  13},
                                                    {0b0000000010001,    9,  2,  13},
                                                    {0b0000000010000,    10, 2,  13},
                                                    {0b0000000011111,    22, 1,  13},
                                                    {0b0000000011110,    23, 1,  13},
                                                    {0b0000000011101,    24, 1,  13},
                                                    {0b0000000011100,    25, 1,  13},
                                                    {0b0000000011011,    26, 1,  13},
                                                    {0b00000000011111,   0,  16, 14},
                                                    {0b00000000011110,   0,  17, 14},
                                                    {0b00000000011101,   0,  18, 14},
                                                    {0b00000000011100,   0,  19, 14},
                                                    {0b00000000011011,   0,  20, 14},
                                                    {0b00000000011010,   0,  21, 14},
                                                    {0b00000000011001,   0,  22, 14},
                                                    {0b00000000011000,   0,  23, 14},
                                                    {0b00000000010111,   0,  24, 14},
                                                    {0b00000000010110,   0,  25, 14},
                                                    {0b00000000010101,   0,  26, 14},
                                                    {0b00000000010100,   0,  27, 14},
                                                    {0b00000000010011,   0,  28, 14},
                                                    {0b00000000010010,   0,  29, 14},
                                                    {0b00000000010001,   0,  30, 14},
                                                    {0b00000000010000,   0,  31, 14},
                                                    {0b000000000011000,  0,  32, 15},
                                                    {0b000000000010111,  0,  33, 15},
                                                    {0b000000000010110,  0,  34, 15},
                                                    {0b000000000010101,  0,  35, 15},
                                                    {0b000000000010100,  0,  36, 15},
                                                    {0b000000000010011,  0,  37, 15},
                                                    {0b000000000010010,  0,  38, 15},
                                                    {0b000000000010001,  0,  39, 15},
                                                    {0b000000000010000,  0,  40, 15},
                                                    {0b000000000011111,  1,  8,  15},
                                                    {0b000000000011110,  1,  9,  15},
                                                    {0b000000000011101,  1,  10, 15},
                                                    {0b000000000011100,  1,  11, 15},
                                                    {0b000000000011011,  1,  12, 15},
                                                    {0b000000000011010,  1,  13, 15},
                                                    {0b000000000011001,  1,  14, 15},
                                                    {0b0000000000010011, 1,  15, 16},
                                                    {0b0000000000010010, 1,  16, 16},
                                                    {0b0000000000010001, 1,  17, 16},
                                                    {0b0000000000010000, 1,  18, 16},
                                                    {0b0000000000010100, 6,  3,  16},
                                                    {0b0000000000011010, 11, 2,  16},
                                                    {0b0000000000011001, 12, 2,  16},
                                                    {0b0000000000011000, 13, 2,  16},
                                                    {0b0000000000010111, 14, 2,  16},
                                                    {0b0000000000010110, 15, 2,  16},
                                                    {0b0000000000010101, 16, 2,  16},
                                                    {0b0000000000011111, 27, 1,  16},
                                                    {0b0000000000011110, 28, 1,  16},
                                                    {0b0000000000011101, 29, 1,  16},
                                                    {0b0000000000011100, 30, 1,  16},
                                                    {0b0000000000011011, 31, 1,  16}};

BlockParser::vlc_signed BlockParser::table_b15[] = {{0b10,               0,  1,  2},
                                                    {0b010,              1,  1,  3},
                                                    {0b110,              0,  2,  3},
                                                    {0b00101,            2,  1,  5},
                                                    {0b0111,             0,  3,  4},
                                                    {0b00111,            3,  1,  5},
                                                    {0b000110,           4,  1,  6},
                                                    {0b00110,            1,  2,  5},
                                                    {0b000111,           5,  1,  6},
                                                    {0b0000110,          6,  1,  7},
                                                    {0b0000100,          7,  1,  7},
                                                    {0b11100,            0,  4,  5},
                                                    {0b0000111,          2,  2,  7},
                                                    {0b0000101,          8,  1,  7},
                                                    {0b1111000,          9,  1,  7},
                                                    {0b11101,            0,  5,  5},
                                                    {0b000101,           0,  6,  6},
                                                    {0b1111001,          1,  3,  7},
                                                    {0b00100110,         3,  2,  8},
                                                    {0b1111010,          10, 1,  7},
                                                    {0b00100001,         11, 1,  8},
                                                    {0b00100101,         12, 1,  8},
                                                    {0b00100100,         13, 1,  8},
                                                    {0b000100,           0,  7,  6},
                                                    {0b00100111,         1,  4,  8},
                                                    {0b11111100,         2,  3,  8},
                                                    {0b11111101,         4,  2,  8},
                                                    {0b000000100,        5,  2,  9},
                                                    {0b000000101,        14, 1,  9},
                                                    {0b000000111,        15, 1,  9},
                                                    {0b0000001101,       16, 1,  10},
                                                    {0b1111011,          0,  8,  7},
                                                    {0b1111100,          0,  9,  7},
                                                    {0b00100011,         0,  10, 8},
                                                    {0b00100010,         0,  11, 8},
                                                    {0b00100000,         1,  5,  8},
                                                    {0b0000001100,       2,  4,  10},
                                                    {0b000000011100,     3,  3,  12},
                                                    {0b000000010010,     4,  3,  12},
                                                    {0b000000011110,     6,  2,  12},
                                                    {0b000000010101,     7,  2,  12},
                                                    {0b000000010001,     8,  2,  12},
                                                    {0b000000011111,     17, 1,  12},
                                                    {0b000000011010,     18, 1,  12},
                                                    {0b000000011001,     19, 1,  12},
                                                    {0b000000010111,     20, 1,  12},
                                                    {0b000000010110,     21, 1,  12},
                                                    {0b11111010,         0,  12, 8},
                                                    {0b11111011,         0,  13, 8},
                                                    {0b11111110,         0,  14, 8},
                                                    {0b11111111,         0,  15, 8},
                                                    {0b0000000010110,    1,  6,  13},
                                                    {0b0000000010101,    1,  7,  13},
                                                    {0b0000000010100,    2,  5,  13},
                                                    {0b0000000010011,    3,  4,  13},
                                                    {0b0000000010010,    5,  3,  13},
                                                    {0b0000000010001,    9,  2,  13},
                                                    {0b0000000010000,    10, 2,  13},
                                                    {0b0000000011111,    22, 1,  13},
                                                    {0b0000000011110,    23, 1,  13},
                                                    {0b0000000011101,    24, 1,  13},
                                                    {0b0000000011100,    25, 1,  13},
                                                    {0b0000000011011,    26, 1,  13},
                                                    {0b00000000011111,   0,  16, 14},
                                                    {0b00000000011110,   0,  17, 14},
                                                    {0b00000000011101,   0,  18, 14},
                                                    {0b00000000011100,   0,  19, 14},
                                                    {0b00000000011011,   0,  20, 14},
                                                    {0b00000000011010,   0,  21, 14},
                                                    {0b00000000011001,   0,  22, 14},
                                                    {0b00000000011000,   0,  23, 14},
                                                    {0b00000000010111,   0,  24, 14},
                                                    {0b00000000010110,   0,  25, 14},
                                                    {0b00000000010101,   0,  26, 14},
                                                    {0b00000000010100,   0,  27, 14},
                                                    {0b00000000010011,   0,  28, 14},
                                                    {0b00000000010010,   0,  29, 14},
                                                    {0b00000000010001,   0,  30, 14},
                                                    {0b00000000010000,   0,  31, 14},
                                                    {0b000000000011000,  0,  32, 15},
                                                    {0b000000000010111,  0,  33, 15},
                                                    {0b000000000010110,  0,  34, 15},
                                                    {0b000000000010101,  0,  35, 15},
                                                    {0b000000000010100,  0,  36, 15},
                                                    {0b000000000010011,  0,  37, 15},
                                                    {0b000000000010010,  0,  38, 15},
                                                    {0b000000000010001,  0,  39, 15},
                                                    {0b000000000010000,  0,  40, 15},
                                                    {0b000000000011111,  1,  8,  15},
                                                    {0b000000000011110,  1,  9,  15},
                                                    {0b000000000011101,  1,  10, 15},
                                                    {0b000000000011100,  1,  11, 15},
                                                    {0b000000000011011,  1,  12, 15},
                                                    {0b000000000011010,  1,  13, 15},
                                                    {0b000000000011001,  1,  14, 15},
                                                    {0b0000000000010011, 1,  15, 16},
                                                    {0b0000000000010010, 1,  16, 16},
                                                    {0b0000000000010001, 1,  17, 16},
                                                    {0b0000000000010000, 1,  18, 16},
                                                    {0b0000000000010100, 6,  3,  16},
                                                    {0b0000000000011010, 11, 2,  16},
                                                    {0b0000000000011001, 12, 2,  16},
                                                    {0b0000000000011000, 13, 2,  16},
                                                    {0b0000000000010111, 14, 2,  16},
                                                    {0b0000000000010110, 15, 2,  16},
                                                    {0b0000000000010101, 16, 2,  16},
                                                    {0b0000000000011111, 27, 1,  16},
                                                    {0b0000000000011110, 28, 1,  16},
                                                    {0b0000000000011101, 29, 1,  16},
                                                    {0b0000000000011100, 30, 1,  16},
                                                    {0b0000000000011011, 31, 1,  16}};

void BlockParser::block(size_t i, Block **destination) {
    PictureDecoder *pictureDecoder = VideoDecoder::getInstance()->getPictureDecoder();
    Block::initializerStruct init = {};
    init.i = i;
    init.QFS = (int *) calloc(64, sizeof(int));
    bool pattern_code[12];
    // tableFlag = true means use Table B.15, otherwise use Table B.14
    bool tableFlag = pictureDecoder->isMacroblockIntra() && pictureDecoder->isIntraVlcFormat();
    initializePatternCode(pattern_code);
    init.cc = Block::calculateCC(i);
    if (pattern_code[i]) {
        unsigned char n = 0;
        if (pictureDecoder->isMacroblockIntra()) {
            init.dct_dc_size = getDctDcSize(init.cc);
            if (init.dct_dc_size != 0) {
                init.dct_dc_differential = (short) read(init.dct_dc_size);
            }
            buildDCCoefficient(init.dct_dc_size, init.dct_dc_differential, &n, init.QFS,
                               init.cc); //Handle First Coefficient
        } else {
            handleCoefficients(tableFlag, &n, init.QFS);
        }
        while (!checkEndCode(tableFlag) && n < 64) {
            handleCoefficients(tableFlag, &n, init.QFS);
        }
        *destination = new Block(init);
    }
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
            if (pictureDecoder->getCbp() & (1u << (5u - i))) pattern_code[i] = true;
        }
        if (VideoInformation::getInstance()->getChromaFormat() ==
            SequenceExtensionPacket::chroma_format_type::cf_422) {
            for (int i = 6; i < 8; i++) {
                if (pictureDecoder->getCodedBlockPattern1() & (1u << (7u - i))) pattern_code[i] = true;
            }
        }
        if (VideoInformation::getInstance()->getChromaFormat() ==
            SequenceExtensionPacket::chroma_format_type::cf_444) {
            for (int i = 6; i < 12; i++) {
                if (pictureDecoder->getCodedBlockPattern2() & (1u << (11u - i))) pattern_code[i] = true;
            }
        }
    }
}

unsigned char BlockParser::getDctDcSize(unsigned char cc) {
    return cc == 0 ? getDctDcSizeLuminance() : getDctDcSizeChrominance();
}

int BlockParser::readSign(int level) {
    bool isNegative = (bool) read(1);
    return isNegative ? -level : level;
}

bool BlockParser::checkEndCode(bool tableFlag) {
    if (!tableFlag && peek(2) == 0b10) {
        read(2);
        return true;
    } else if (tableFlag && peek(4) == 0b0110) {
        read(4);
        return true;
    }
    return false;
}

BlockParser::vlc_signed BlockParser::getVLCCode(bool tableFlag) {
    if (!tableFlag) {
        for (vlc_signed code: table_b14) {
            if (peek(code.numbits) == code.key) {
                read(code.numbits);
                return code;
            }
        }
        throw PacketException("BlockParser::getVLCCode: B14 VLC not found\n");
    } else {
        for (vlc_signed code: table_b15) {
            if (peek(code.numbits) == code.key) {
                read(code.numbits);
                return code;
            }
        }
        throw PacketException("BlockParser::getVLCCode: B15 VLC not found\n");
    }
}

void BlockParser::populateQFS(unsigned char *n, int *QFS, int signed_level, unsigned char run) {
    for (size_t m = 0; m < run; m++) {
        QFS[*n] = 0;
        (*n)++;
    }
    QFS[*n] = signed_level;
    (*n)++;
    if (*n > 64) {
        throw PacketException("BlockParser::populateQFS: error decoding VLC, out of bounds write\n");
    }
}

short BlockParser::escapeSignHelper(short signed12BitValue) {
    if ((signed12BitValue & 0b100000000000) == 0b100000000000) { // NOLINT(hicpp-signed-bitwise)
        return (short) (0xF000 | signed12BitValue); // NOLINT(hicpp-signed-bitwise)
    }
    return signed12BitValue;
}

void BlockParser::buildDCCoefficient(unsigned char dct_dc_size, int dct_dc_differential, unsigned char *n,
                                     int *QFS, unsigned char cc) {
    PictureDecoder *pictureDecoder = VideoDecoder::getInstance()->getPictureDecoder();
    int dct_diff;
    if (dct_dc_size == 0) {
        dct_diff = 0;
    } else {
        int half_range = integerPow(2, dct_dc_size - 1);
        if (dct_dc_differential >= half_range) {
            dct_diff = dct_dc_differential;
        } else {
            dct_diff = (dct_dc_differential + 1) - (2 * half_range);
        }
    }
    QFS[0] = pictureDecoder->getDctDcPred(cc) + dct_diff;
    pictureDecoder->setDctDcPred(cc, QFS[0]);
    (*n)++;
}

void BlockParser::handleCoefficients(bool tableFlag, unsigned char *n, int *QFS) {
    int signed_level;
    unsigned char run;
    if (*n == 0) {
        if (peek(1) == 1) {
            read(1);
            signed_level = readSign(1);
            run = 0;
            populateQFS(n, QFS, signed_level, run);
            return;
        }
    }
    if (peek(6) == 0b000001) {
        read(6);
        run = (unsigned char) read(6);
        auto signed12BitInteger = (short) read(12);
        signed_level = escapeSignHelper(signed12BitInteger);
    } else {
        vlc_signed code = getVLCCode(tableFlag);
        signed_level = readSign(code.level);
        run = code.run;
    }
    populateQFS(n, QFS, signed_level, run);
}

/**
 * Calculates base ^ exp. Does not handle edge cases that the decoder doesn't handle
 * @param base
 * @param exp
 * @return
 */
int BlockParser::integerPow(int base, int exp) {
    int out = 1;
    for (int i = 0; i < exp; i++) {
        out = out * base;
    }
    return out;
}
