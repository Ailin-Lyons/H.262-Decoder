//
// Created by elnsa on 2020-01-17.
//

#include "gtest/gtest.h"
#include "../../../Util/FileInterface.h"
#include "../../../StreamParsers/ESParser.h"
#include "../../../StreamPackets/ESPackets/Slice/SlicePacket.h"

TEST(AllTest, SliceParser_Test) {
    SlicePacket expected = SlicePacket({});//TODO
    char relative_path[] = R"(..\..\..\test files/Single Packets/testvideo_noaudio.ts)";
    FileInterface::getInstance()->setInstance(relative_path);
    ESParser::getInstance()->initiateStream();
    while (ESPacket::getStartCode(ESParser::getInstance()->nextESPacketID()) !=
           ESPacket::start_code::sequence_header) {
        ESParser::getInstance()->getNextPacket();
    }
    SlicePacket *actual = (SlicePacket *) ESParser::getInstance()->getNextPacket();
    ASSERT_EQ(expected, *actual);
}