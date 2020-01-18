//
// Created by elnsa on 2020-01-17.
//

#include "gtest/gtest.h"
#include "../../../Util/FileInterface.h"
#include "../../../PacketParsers/ESParser.h"
#include "../../../ESPackets/RegularStartCodes/SequenceDisplayExtensionPacket.cpp"
#include "../../../ESPackets/RegularStartCodes/ExtensionPacket.h"

TEST(AllTest, SequenceDisplayExtension_Parser_Test) {
    SequenceDisplayExtensionPacket::initializerStruct init{};
    init.video_format = 0x5;
    init.colour_description = true;
    init.colour_primaries = 0x5;
    init.transfer_characteristics = 0x1;
    init.matrix_coefficients = 0x5;
    init.display_horizontal_size = 0x500;
    init.display_vertical_size = 0x2D0;
    SequenceDisplayExtensionPacket expected = SequenceDisplayExtensionPacket(init);
    char relative_path[] = R"(..\..\..\test files\testvideo_noaudio.ts)";
    FileInterface::getInstance()->setInstance(relative_path);
    ESParser::getInstance()->initiateStream();
    bool testDone = true;
    while (testDone) {
        if (ESPacket::getStartCode(ESParser::getInstance()->nextESPacketID()) ==
            ESPacket::start_code::extension) {
            auto *actual = (ExtensionPacket *) ESParser::getInstance()->getNextPacket();
            if (actual->getExtensionType() == ExtensionPacket::extension_type::sequence_display) {
                ASSERT_EQ(expected, *((SequenceDisplayExtensionPacket *) actual));
                testDone = false;
            }
        } else {
            ESParser::getInstance()->getNextPacket();
        }
    }
}