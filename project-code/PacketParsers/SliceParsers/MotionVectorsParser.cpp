//
// Created by elnsa on 2020-01-19.
//
#include "ESParser.h"
#include "../../ESPackets/Slice/MotionVectors.h"

#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

class MotionVectorsParser {
public:
    /**
     * Builds a MotionVectors() from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.5.2.1
     */
    static MotionVectors *motion_vectors(size_t i, MotionVectors **out) {
        return nullptr; //TODO
    }
};