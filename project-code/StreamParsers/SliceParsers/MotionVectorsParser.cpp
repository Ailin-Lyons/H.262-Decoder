//
// Created by elnsa on 2020-01-19.
//
#include "ESParser.h"
#include "../../PictureDecoder/Slice/MotionVectors.h"
#include "../../VideoDecoder/VideoDecoder.h"
#include "MotionVectorParser.cpp"

#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

class MotionVectorsParser {
public:
    /**
     * Builds a MotionVectors() from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.5.2.1
     */

    // Note - s indicates the forward or backward type for the motion vector

    static MotionVectors *motion_vectors(int s) {
        MotionVectors::initializerStruct init{false, false,
                                              nullptr, nullptr};
        PictureDecoder *pictureDecoder = VideoDecoder::getInstance()->getPictureDecoder();
        int motion_vector_count;
        bool mv_format = pictureDecoder->getFrameMotionType() == 0b10; //Note - true = frame, false = field
        bool dmv = (pictureDecoder->getFrameMotionType() == 0b11) || (pictureDecoder->getFieldMotionType() == 0b11);
        if (pictureDecoder->getFieldMotionType() != 0b00) {
            motion_vector_count = pictureDecoder->getFieldMotionType() == 0b10 ? 2 : 1;
        } else {
            motion_vector_count = pictureDecoder->getFrameMotionType() == 0b01 ?
                                  (pictureDecoder->getSpatialTemporalWeightClass() > 1 ? 1 : 2) : 1;
        }
        if (motion_vector_count == 1) {
            if (!mv_format && !dmv) {
                init.motion_vertical_field_select_0_s = read(1);
            }
            init.motion_vector_0_s = MotionVectorParser::getNextPacket(0, s);
        } else {
            init.motion_vertical_field_select_0_s = read(1);
            init.motion_vector_0_s = MotionVectorParser::getNextPacket(0, s);
            init.motion_vertical_field_select_1_s = read(1);
            init.motion_vector_1_s = MotionVectorParser::getNextPacket(1, s);
        }
        return new MotionVectors(init);
    }
};