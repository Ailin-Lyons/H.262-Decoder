//
// Created by elnsa on 2020-01-15.
//
#include "ESParser.h"
#include "../../PictureDecoder/Slice/Slice.h"
#include "../../VideoDecoder/VideoInformation.h"
#include "../../VideoDecoder/VideoInformation.cpp" //Initialize singleton for tests
#include "MacroblockParser.h"
#include "../../VideoDecoder/VideoDecoder.h"

#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

class SliceParser {
public:
    /**
     * Builds a Slice from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.4
     */
    static Slice *getNextPacket(unsigned char stream_id) {
        VideoDecoder::getInstance()->getPictureDecoder()->resetDctDcPred(); // resetting dct_dc_pred as per Table 7-2
        Slice::initializerStruct init = {};
        init.stream_id = stream_id;
        if (VideoInformation::getInstance()->getVerticalSize() > 2800) {
            init.slice_vertical_position_extension = (unsigned char) read(3);
        }
//        if(<sequence_scalable_extension() is present in the bitstream>) { //This feature is not covered by this decoder
//            if (scalable_mode == 0x00) {
//                priority_breakpoint = read(7);
//            }
//        }
        init.quantiser_scale_code = (unsigned char) read(5);
        if (peek(1) == 1) {
            init.slice_extension_flag = (bool) read(1);
            init.intra_slice = (bool) read(1);
            init.slice_picture_id_enable = (bool) read(1);
            init.slice_picture_id = (unsigned char)read(6);
            while (peek(1) == 1) {
                read(9); //extra_information_slice is not handled by this decoder
            }
        }
        read(1); //extra_bit_slice
        init.numMacroblocks = 0;
        init.macroblocks = (Macroblock *) malloc(sizeof(Macroblock) * 1);
        do {
            init.numMacroblocks++;
            init.macroblocks = (Macroblock *) realloc(init.macroblocks, sizeof(Macroblock) * init.numMacroblocks);
            init.macroblocks[init.numMacroblocks - 1] = *MacroblockParser::getNextPacket(init.quantiser_scale_code);
        } while (peek(23) != 0x000000);
        return new Slice(init);
    }
};
