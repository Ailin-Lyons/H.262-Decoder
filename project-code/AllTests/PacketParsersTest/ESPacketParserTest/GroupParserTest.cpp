//
// Created by elnsa on 2020-01-17.
//

#include "gtest/gtest.h"
#include "../../../Util/FileInterface.h"
#include "../../../StreamParsers/ESParser.h"
#include "../../../StreamPackets/ESPackets/RegularStartCodes/GroupOfPicturesHeaderPacket.h"

TEST(AllTest, GroupOfPicturesHeaderPacket_Test) {
    GroupOfPicturesHeaderPacket::initializerStruct init{};
    init.time_code = 0x1000;
    init.closed_gop = true;
    init.broken_link = false;
    GroupOfPicturesHeaderPacket expected = GroupOfPicturesHeaderPacket(init);
    char relative_path[] = R"(..\..\..\test files\testvideo_noaudio.ts)";
    FileInterface::getInstance()->setInstance(relative_path);
    ESParser::getInstance()->initiateStream();
    while (ESPacket::getStartCode(ESParser::getInstance()->nextESPacketID()) != ESPacket::start_code::group) {
        ESParser::getInstance()->getNextPacket();
    }
    auto *actual = (GroupOfPicturesHeaderPacket *) ESParser::getInstance()->getNextPacket();
    ASSERT_EQ(expected, *actual);
}