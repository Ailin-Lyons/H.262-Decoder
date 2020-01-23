//
// Created by elnsa on 2020-01-22.
//

#ifndef PROJECT_CODE_MOTIONVECTORPARSER_H
#define PROJECT_CODE_MOTIONVECTORPARSER_H

#include "ESParser.h"
#include "../../ESPackets/Slice/MotionVector.h"

#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

class MotionVectorParser {
private:
    struct vlc {
        unsigned char numbits;
        char value;
        unsigned short key;
    };
    static vlc table_b10[];
    static size_t table_b10_size;
    static vlc table_b11[];
    static size_t table_b11_size;
public:
    /**
     * Builds a MotionVector() from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.5.2.1
     */
    static MotionVector *getNextPacket(int r, int s);

private:
    /**
     * this function would deal with MotionVector
     * @param val
     * @return
     */
    static int parse_motion_code();

    static int parse_dmv_code();

    static unsigned char parse_motion_residual();
};


#endif //PROJECT_CODE_MOTIONVECTORPARSER_H
