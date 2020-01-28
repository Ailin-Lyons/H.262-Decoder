//
// Created by elnsa on 2020-01-17.
//

#include "gtest/gtest.h"
#include "../../../Util/FileInterface.h"
#include "../../../StreamParsers/ESParser.h"
#include "../../../StreamPackets/ESPackets/RegularStartCodes/PictureCodingExtensionPacket.cpp"
#include "../../../StreamPackets/ESPackets/RegularStartCodes/ExtensionPacket.h"

TEST(AllTest, PictureCodingExtension_Parser_Test) {
    PictureCodingExtensionPacket::initializerStruct init{};
    init.f_code_0_0 = 0xF;
    init.f_code_0_1 = 0xF;
    init.f_code_1_0 = 0xF;
    init.f_code_1_1 = 0xF;
    init.intra_dc_precision = PictureCodingExtensionPacket::intra_dc_precision_bits::p_8;
    init.picture_structure = PictureCodingExtensionPacket::picture_structure_types ::frame;
    init.top_field_first = false;
    init.frame_pred_frame_dct = true;
    init.concealment_motion_vectors = false;
    init.q_scale_type = false;
    init.intra_vlc_format = false;
    init.alternate_scan = false;
    init.repeat_first_field = false;
    init.chroma_420_type = true;
    init.progressive_frame = true;
    init.composite_display_flag = false;
    PictureCodingExtensionPacket expected = PictureCodingExtensionPacket(init);
    char relative_path[] = R"(../../../test files/testvideo_noaudio.ts)";
    FileInterface::getInstance()->setInstance(relative_path);
    ESParser::getInstance()->initiateStream();
    bool testDone = true;
    while (testDone) {
        if (ESPacket::getStartCode(ESParser::getInstance()->nextESPacketID()) ==
            ESPacket::start_code::extension) {
            auto *actual = (ExtensionPacket *) ESParser::getInstance()->getNextPacket();
            if (actual->getExtensionType() == ExtensionPacket::extension_type::picture_coding) {
                ASSERT_EQ(expected, *((PictureCodingExtensionPacket *) actual));
                testDone = false;
            }
        } else {
            ESParser::getInstance()->getNextPacket();
        }
    }
}