//
// Created by elnsa on 2020-01-15.
//
#include "ESParser.h"
#include "../../StreamPackets/ESPackets/Slice/SlicePacket.h"
#include "../../VideoDecoder/VideoInformation.h"
#include "../../VideoDecoder/VideoInformation.cpp" //Initialize singleton for tests
#include "MacroblockParser.h"

#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

class SliceParser {
public:
    /**
     * Builds a SlicePacket from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.4
     */
    static SlicePacket *getNextPacket(unsigned char stream_id) {
        SlicePacket::initializerStruct init = {};
        init.stream_id = stream_id;
        if (VideoInformation::getInstance()->getVerticalSize() > 2800) {
            init.slice_vertical_position_extension = read(3);
        }
//        if(<sequence_scalable_extension() is present in the bitstream>) { //This feature is not covered by this decoder
//            if (scalable_mode == 0x00) {
//                priority_breakpoint = read(7);
//            }
//        }
        init.quantiser_scale_code = read(5);
        if (peek(1) == 1) {
            init.slice_extension_flag = read(1);
            init.intra_slice = read(1);
            init.slice_picture_id_enable = read(1);
            init.slice_picture_id = read(6);
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
            init.macroblocks[init.numMacroblocks-1] = *MacroblockParser::getNextPacket();
        } while (peek(23) != 0x000000);
        return new SlicePacket(init);
    }
};
