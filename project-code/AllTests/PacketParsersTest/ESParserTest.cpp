//
// Created by elnsa on 2020-01-13.
//

#include "gtest/gtest.h"
#include "../../Util/FileInterface.h"
#include "../../PacketParsers/ESParser.h"
//TODO write tests the H262 portion of this class

TEST(AllTest, ESParser_video_stream_only) {
    char relative_path[] = R"(..\..\..\test files/testvideo_noaudio.ts)";
    FileInterface::getInstance()->setInstance(relative_path);
    ESParser* esParser = ESParser::getInstance();
    esParser->initiateStream();
    ASSERT_EQ(esParser->program_pid, 0x64);
}

TEST(AllTest, ESParser_tstream_contains_audio) {
    char relative_path[] = R"(..\..\..\test files/testvideo.ts)";
    FileInterface::getInstance()->setInstance(relative_path);
    ESParser* esParser = ESParser::getInstance();
    esParser->initiateStream();
    ASSERT_EQ(esParser->program_pid, 0x100);
}

TEST(AllTest, ESParser_peek_pop) {
    char relative_path[] = R"(..\..\..\test files/testvideo_noaudio.ts)";
    FileInterface::getInstance()->setInstance(relative_path);
    ESParser* esParser = ESParser::getInstance();
    esParser->initiateStream();
    unsigned long long val = esParser->popNBits(32);
    ASSERT_EQ(val,0x000001E0);
    val = esParser->peekNBits(64);
    ASSERT_EQ(val,0x0000848005210003);
    val = esParser->peekNBits(64);
    ASSERT_EQ(val,0x0000848005210003);
    val = esParser->popNBits(32);
    ASSERT_EQ(val,0x00008480);
    val = esParser->popNBits(64);
    ASSERT_EQ(val,0x0521000319410000);
    for(int i = 0; i < 19; i++){
        val = esParser->popNBits(64);
    }
    val = esParser->popNBits(32);
    val = esParser->peekNBits(64);
    ASSERT_EQ(val,0x9A03A018945ABF6E);
    val = esParser->popNBits(64);
    ASSERT_EQ(val,0x9A03A018945ABF6E);
    ASSERT_ANY_THROW(esParser->popNBits(100));
}