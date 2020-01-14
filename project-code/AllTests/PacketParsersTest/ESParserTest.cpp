//
// Created by elnsa on 2020-01-13.
//

#include "gtest/gtest.h"
#include "../../Util/FileInterface.h"
#include "../../PacketParsers/ESParser.h"

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

