//
// Created by elnsa on 2020-01-17.
//

#include "gtest/gtest.h"
#include "../../../Util/FileInterface.h"
#include "../../../PacketParsers/ESParser.h"
#include "../../../ESPackets/RegularStartCodes/PictureHeaderPacket.h"

TEST(AllTest, PictureHeaderPacket_Test) {
    PictureHeaderPacket expected = PictureHeaderPacket({});//TODO
    char relative_path[] = R"(..\..\..\test files/Single Packets/testvideo_noaudio.ts)";
    FileInterface::getInstance()->setInstance(relative_path);
    ESParser::getInstance()->initiateStream();
    while (ESPacket::getStartCode(ESParser::getInstance()->nextESPacketID()) != ESPacket::start_code::picture) {
        ESParser::getInstance()->getNextPacket();
    }
    PictureHeaderPacket *actual = (PictureHeaderPacket *) ESParser::getInstance()->getNextPacket();
    ASSERT_EQ(expected, *actual);
}