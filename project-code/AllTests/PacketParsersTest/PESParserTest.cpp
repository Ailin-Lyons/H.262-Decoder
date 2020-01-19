//
// Created by elnsa on 2020-01-17.
//

#include "gtest/gtest.h"
#include "../../Util/FileInterface.h"
#include "../../PacketParsers/PESParser.cpp"

TEST(AllTest, PESParser_Test) {
    PESPacket::pts_dts_fields pts_dts = {0x8CA0, 0};
    PESPacket::dsm_trick_mode_fields dsmtmf = {};
    PESPacket::PES_extension_fields ppef = {};
    PESPacket expected = PESPacket(ESPacket::start_code::video_stream, 0xE0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 5,
                                   pts_dts, 0, 0, dsmtmf, 0, 0, ppef, 0, 0);
    char relative_path[] = R"(..\..\..\test files\testvideo_noaudio.ts)";
    FileInterface::getInstance()->setInstance(relative_path);
    ESParser::getInstance()->initiateStream();
    while (ESPacket::getStartCode(ESParser::getInstance()->nextESPacketID()) !=
           ESPacket::start_code::video_stream) {
        ESParser::getInstance()->getNextPacket();
    }
    auto *actual = (PESPacket *) ESParser::getInstance()->getNextPacket();
    ASSERT_EQ(expected, *actual);
}


