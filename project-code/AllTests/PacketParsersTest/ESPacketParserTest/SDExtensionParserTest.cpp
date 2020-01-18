//
// Created by elnsa on 2020-01-17.
//

#include "gtest/gtest.h"
#include "../../../Util/FileInterface.h"
#include "../../../PacketParsers/ESParser.h"
#include "../../../ESPackets/RegularStartCodes/SequenceDisplayExtensionPacket.cpp"
#include "../../../ESPackets/RegularStartCodes/ExtensionPacket.h"

TEST(AllTest, SequenceDisplayExtension_Parser_Test) {
    //SequenceDisplayExtensionPacket expected = SequenceDisplayExtensionPacket({});//TODO
    char relative_path[] = R"(..\..\..\test files/Single Packets/testvideo_noaudio.ts)";
    FileInterface::getInstance()->setInstance(relative_path);
    ESParser::getInstance()->initiateStream();
    while (1) {
        if (ESPacket::getStartCode(ESParser::getInstance()->nextESPacketID()) ==
            ESPacket::start_code::extension) {
            ExtensionPacket *actual = (ExtensionPacket *) ESParser::getInstance()->getNextPacket();
            if (actual->getExtensionType() == ExtensionPacket::extension_type::sequence) {
                //ASSERT_EQ(expected, *((SequenceDisplayExtensionPacket *) actual));
                GTEST_FAIL();
                break;
            }
        }
    }
}