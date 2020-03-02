//
// Created by elnsa on 2020-01-17.
//

#include "gtest/gtest.h"
#include "../../../Util/FileInterface.h"
#include "../../../StreamParsers/ESParser.h"
#include "../../../StreamPackets/ESPackets/RegularStartCodes/PictureHeaderPacket.h"

TEST(AllTest, PictureHeaderPacket_Test) {
    PictureHeaderPacket::initializerStruct init{};
    init.picture_coding_type = PictureHeaderPacket::toPictureCodingType(0x1);
    init.temporal_reference = 0x0;
    init.vbv_delay = 0xFFFF;
    PictureHeaderPacket expected = PictureHeaderPacket(init);
    char relative_path[] = R"(../../../testFiles/testvideo_noaudio.ts)";
    FileInterface::getInstance()->setInstance(relative_path);
    ESParser::getInstance()->initiateStream();
    while (ESPacket::getStartCode(ESParser::getInstance()->nextESPacketID()) != ESPacket::start_code::picture) {
        ESParser::getInstance()->getNextPacket();
    }
    auto *actual = (PictureHeaderPacket *) ESParser::getInstance()->getNextPacket();
    ASSERT_EQ(expected, *actual);
}