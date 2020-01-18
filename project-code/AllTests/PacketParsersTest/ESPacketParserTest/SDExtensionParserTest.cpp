//
// Created by elnsa on 2020-01-17.
//

#include "gtest/gtest.h"
#include "../../../Util/FileInterface.h"
#include "../../../PacketParsers/ESParser.h"
#include "../../../ESPackets/RegularStartCodes/SequenceDisplayExtensionPacket.cpp"

TEST(AllTest, SequenceDisplayExtension_Parser_Test) {
    //SequenceDisplayExtensionPacket expected = SequenceDisplayExtensionPacket({});//TODO
    char relative_path[] = R"(..\..\..\test files/Single Packets/testvideo_noaudio.ts)";
    FileInterface::getInstance()->setInstance(relative_path);
    ESParser::getInstance()->initiateStream();
    while (ESPacket::getStartCode(ESParser::getInstance()->nextESPacketID()) !=
           ESPacket::start_code::extension) {     //TODO filter for correct extension type
        ESParser::getInstance()->getNextPacket();
    }
    SequenceDisplayExtensionPacket *actual = (SequenceDisplayExtensionPacket *) ESParser::getInstance()->getNextPacket();
    //ASSERT_EQ(expected, *actual);
}