//
// Created by elnsa on 2020-01-19.
//
#include "ESParser.h"
#include "../../StreamPackets/ESPackets/Slice/Block.h"
#include "../../PictureDecoder/PictureDecoder.h"
#include "../../VideoDecoder/VideoDecoder.h"
#include "../../VideoDecoder/VideoInformation.h"

#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

class BlockParser {
public:
/**
     * Builds a Block() from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.6
     */
    static Block *block(size_t i) {
        PictureDecoder *pictureDecoder = VideoDecoder::getInstance()->getPictureDecoder();
        Block::initializerStruct init = {};
        bool pattern_code[12];
        initializePatternCode(pattern_code);
        if (pattern_code[i]) {
            if (pictureDecoder->isMacroblockIntra()) {
                if (i < 4) {
                    init.dct_dc_size_luminance = getDctDcSizeLuminance();
                    if (init.dct_dc_size_luminance != 0) {
                        init.dct_dc_differential = getDctDcDifferential();
                    }
                } else {
                    init.dct_dc_size_chrominance = getDctDcSizeLuminance();
                    if (init.dct_dc_size_chrominance != 0) {
                        init.dct_dc_differential = getDctDcDifferential();
                    }
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

private:
    static unsigned char getDctDcDifferential() {
        return 0;//TODO
    }

    static unsigned short getDctDcSizeLuminance() {
        return 0;//TODO
    }

    static void initializePatternCode(bool pattern_code[12]) {
        PictureDecoder *pictureDecoder = VideoDecoder::getInstance()->getPictureDecoder();
        for (int i = 0; i < 12; i++) {
            if (pictureDecoder->isMacroblockIntra()) {
                pattern_code[i] = 1;
            } else {
                pattern_code[i] = 0;
            }
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
};

