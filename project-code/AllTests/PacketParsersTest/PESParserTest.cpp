//
// Created by elnsa on 2020-01-17.
//

#include "gtest/gtest.h"
#include "../../Util/FileInterface.h"
#include "../../PacketParsers/PESParser.cpp"

TEST(AllTest, PESParser_Test) {
    //PESPacket expected = PESPacket(TODO initiate test packet);
    char relative_path[] = R"(..\..\..\test files/Single Packets/testvideo_noaudio.ts)";
    FileInterface::getInstance()->setInstance(relative_path);
    ESParser::getInstance()->initiateStream();
    while (ESPacket::getStartCode(ESParser::getInstance()->nextESPacketID()) !=
           ESPacket::start_code::video_stream) {
        ESParser::getInstance()->getNextPacket();
    }
    PESPacket *actual = (PESPacket *) ESParser::getInstance()->getNextPacket();
    //ASSERT_EQ(expected, *actual);
}


