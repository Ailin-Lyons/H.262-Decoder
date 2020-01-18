//
// Created by elnsa on 2020-01-17.
//

#include "gtest/gtest.h"
#include "../../../Util/FileInterface.h"
#include "../../../PacketParsers/ESParser.h"
#include "../../../ESPackets/RegularStartCodes/SequenceHeaderPacket.cpp"

TEST(AllTest, SequenceHeader_Parser_Test) {
    SequenceHeaderPacket::initializerStruct init{};
    init.horizontal_size_value = 0x500;
    init.vertical_size_value = 0x2D0;
    init.aspect_ratio_information = 0x3;
    init.frame_rate_code = 0x3;
    init.bit_rate_value = 0x7D0;
    init.vbv_buffer_size_value = 0xC4;
    init.constrained_parameters_flag = false;
    init.load_intra_quantiser_matrix = false;
    init.intra_quantiser_matrix = nullptr;
    init.non_intra_quantiser_matrix = nullptr;
    init.load_non_intra_quantiser_matrix = false;
    SequenceHeaderPacket expected = SequenceHeaderPacket(init);
    char relative_path[] = R"(..\..\..\test files\testvideo_noaudio.ts)";
    FileInterface::getInstance()->setInstance(relative_path);
    ESParser::getInstance()->initiateStream();
    while (ESPacket::getStartCode(ESParser::getInstance()->nextESPacketID()) !=
           ESPacket::start_code::sequence_header) {
        ESParser::getInstance()->getNextPacket();
    }
    auto *actual = (SequenceHeaderPacket *) ESParser::getInstance()->getNextPacket();
    ASSERT_EQ(expected, *actual);
}