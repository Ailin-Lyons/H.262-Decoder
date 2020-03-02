//
// Created by elnsa on 2020-01-17.
//

#include "gtest/gtest.h"
#include "../../../Util/FileInterface.h"
#include "../../../StreamParsers/ESParser.h"
#include "../../../StreamPackets/ESPackets/RegularStartCodes/SequenceExtensionPacket.h"

TEST(AllTest, SequenceExtension_Parser_Test) {
    SequenceExtensionPacket::initializerStruct init{};
    init.e_type = ExtensionPacket::extension_type::sequence;
    init.profile_and_level_indication = 0x46;
    init.progressive_sequence = true;
    init.chroma_format = SequenceExtensionPacket::chroma_format_type::cf_420;
    init.horizontal_size_extension = 0x0;
    init.vertical_size_extension = 0x0;
    init.bit_rate_extension = 0x0;
    init.vbv_buffer_size_extension = 0x0;
    init.low_delay = true;
    init.frame_rate_extension_n = 0;
    init.frame_rate_extension_d = 0;
    SequenceExtensionPacket expected = SequenceExtensionPacket(init);
    char relative_path[] = R"(../../../testFiles/testvideo_noaudio.ts)";
    FileInterface::getInstance()->setInstance(relative_path);
    ESParser::getInstance()->initiateStream();
    while (ESPacket::getStartCode(ESParser::getInstance()->nextESPacketID()) !=
           ESPacket::start_code::extension) {
        ESParser::getInstance()->getNextPacket();
    }
    auto *actual = (SequenceExtensionPacket *) ESParser::getInstance()->getNextPacket();
    ASSERT_EQ(expected, *actual);
}