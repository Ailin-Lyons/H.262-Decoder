//
// Created by elnsa on 2020-01-15.
//
#include "../ESParser.h"
#include "../../ESPackets/RegularStartCodes/SlicePacket.h"
#include "../../VideoDecoder/VideoInformation.h"

#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

class SliceParser {
public:
    /**
     * // TODO write comment
     */
    static SlicePacket *getNextPacket(unsigned char stream_id) {
        unsigned int slice_start_code = (0x000001 << 8) + stream_id;
        unsigned char slice_vertical_position_extension = 0;
        if (VideoInformation::getInstance()->getVerticalSize() > 2800) {
            slice_vertical_position_extension = read(3);
        }
        unsigned char priority_breakpoint = 0;
//        if(<sequence_scalable_extension() is present in the bitstream>) { //This feature is not covered by this decoder
//            if (scalable_mode == 0x00) {
//                priority_breakpoint = read(7);
//            }
//        }
        unsigned char quantiser_scale_code = read(5);
        unsigned char slice_extension_flag = 0;
        unsigned char intra_slice = 0;
        unsigned char slice_picture_id_enable = 0;
        unsigned char slice_picture_id = 0;
        size_t numExtraInfo = 0;
        SlicePacket::extraInformation *extra_Information = nullptr;
        if (peek(1) == 1) {
            read(1);
            slice_extension_flag = read(1);
            intra_slice = read(1);
            slice_picture_id_enable = read(1);
            slice_picture_id = read(6);
            while (peek(1) == 1) {
                read(1);
                extra_Information = (SlicePacket::extraInformation *) realloc(extra_Information,
                                                                              sizeof(SlicePacket::extraInformation) *
                                                                              (numExtraInfo + 1));
                extra_Information[numExtraInfo].extra_bit_slice = read(1);
                extra_Information[numExtraInfo].extra_information_slice = read(8);
                numExtraInfo++;
            }
        }
        unsigned char extra_bit_slice = read(1);
        //TODO macroblock
        return new SlicePacket(
                SlicePacket::initializerStruct{stream_id, slice_start_code, slice_vertical_position_extension,
                                               priority_breakpoint, quantiser_scale_code, slice_extension_flag,
                                               intra_slice, slice_picture_id_enable, slice_picture_id,
                                               numExtraInfo, extra_Information, extra_bit_slice});
    }
};
