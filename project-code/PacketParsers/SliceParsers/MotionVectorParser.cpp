//
// Created by elnsa on 2020-01-19.
//
#include "ESParser.h"
#include "../../ESPackets/Slice/MotionVector.h"

#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

class MotionVectorParser {
public:
    /**
     * Builds a MotionVector() from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.5.2.1
     */
    static MotionVector *getNextPacket(int r, int s) {
        return nullptr; //TODO
    }

private:
    /**
     * this function would deal with MotionVector
     * @param val
     * @return
     */
    static int parse_motion_code(int* val) {
        return 0;
    }
};
