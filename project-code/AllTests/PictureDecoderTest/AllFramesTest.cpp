//
// Created by bhave on 3/1/2020.
//

#include "gtest/gtest.h"
#include <iostream>
#include <dirent.h>
#include "../../CImg283/CImg.h"

class frameTest : public ::testing::Test {
protected:

    /** change dirPath to the directory containing the testFrames as needed
     * each frame should be of the form "frame\d+.bmp"
     */

    std::string dirPath = "../../../testFiles/testFrames/";

    int countNumFiles() {
        DIR *dp;
        int i = 0;
        struct dirent *ep;
        dp = opendir (dirPath.c_str());

        if (dp != nullptr)
        {
            while ((ep = readdir (dp)))
                i++;

            (void) closedir (dp);
        }
        return i-2;
    }

    std::string genFileName(int i, int total) {
        std::string frameNum = std::to_string(i);
        while(frameNum.length() < std::to_string(total).length()) {
            frameNum.insert(0, 1, '0');
        }
        frameNum.insert(0, dirPath);
        frameNum.append(".bmp");
        return frameNum;
    }
};


TEST_F(frameTest, frameTest_OverallTest) {
    int frame = 0;
    int totalFrames = countNumFiles();
    while (frame < totalFrames) {
        frame++;
        std::string frameNum = genFileName(frame, totalFrames);
        try {
            cimg_library::CImg<int> image = cimg_library::CImg<>().load_bmp(frameNum.c_str());
            // Todo - write the actual test
        } catch(cimg_library::CImgException& e) {
            break;
        }
    }
}