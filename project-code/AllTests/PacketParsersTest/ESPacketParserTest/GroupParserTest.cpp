//
// Created by elnsa on 2020-01-17.
//

#include "gtest/gtest.h"
#include "../../../Util/FileInterface.h"
#include "../../../PacketParsers/ESParser.h"
#include "../../../ESPackets/RegularStartCodes/GroupOfPicturesHeaderPacket.h"

TEST(AllTest, GroupOfPicturesHeaderPacket_Test) {
    GroupOfPicturesHeaderPacket expected = GroupOfPicturesHeaderPacket({});//TODO
    char relative_path[] = R"(..\..\..\test files/Single Packets/testvideo_noaudio.ts)";
    FileInterface::getInstance()->setInstance(relative_path);
    ESParser::getInstance()->initiateStream();
    while (ESPacket::getStartCode(ESParser::getInstance()->nextESPacketID()) != ESPacket::start_code::group) {
        ESParser::getInstance()->getNextPacket();
    }
    auto *actual = (GroupOfPicturesHeaderPacket *) ESParser::getInstance()->getNextPacket();
    ASSERT_EQ(expected, *actual);
}