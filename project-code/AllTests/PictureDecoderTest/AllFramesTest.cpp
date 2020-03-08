//
// Created by bhave on 3/1/2020.
//

#include "gtest/gtest.h"
#include <iostream>
#include <dirent.h>
#include "../../CImg283/CImg.h"
#include "../../VideoDecoder/VideoDecoder.h"
#include <malloc.h>
#include <cmath>

class frameTest : public ::testing::Test {
protected:

    /** change dirPath to the directory containing the testFrames as needed
     * each frame should be of the form "\d+.bmp"
     */

    std::string dirPath = "../../../testFiles/testFrames/";
    double allowedRmsError = 0; // todo set it to a reasonable number

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

    std::string genFileName(int i, size_t length) {
        std::string frameNum = std::to_string(i);
        while(frameNum.length() < length) {
            frameNum.insert(0, 1, '0');
        }
        frameNum.insert(0, dirPath); // todo redo this to not have frame
        frameNum.append(".bmp");
        return frameNum;
    }

    static double testOneFrame(const cimg_library::CImg<int> &expected, const cimg_library::CImg<int> &actual) {
        if (expected.size() == actual.size()) {
            double out = 0;
            const int* expectedData = expected.data();
            const int* actualData = actual.data();
            size_t i = expected.size();
            if (i == 0) {
                return DBL_MAX;
            }
            while(i-->0) {
                out += pow(expected[i] - actual[i], 2);
            }
            out = out / expected.size();
            return sqrt(out);
        }
        return DBL_MAX;
    }

    cimg_library::CImg<int>* generateNextFrame() {
        return nullptr; // todo
    }
};


TEST_F(frameTest, OverallTest) {
    int frame = 0;
    int totalFrames = countNumFiles();
    size_t lengthOfFrameNum = std::to_string(countNumFiles()).length();
    while (frame < totalFrames) {
        frame++;
        std::string frameNum = genFileName(frame, lengthOfFrameNum);
        try {
            cimg_library::CImg<int> image = cimg_library::CImg<>().load_bmp(frameNum.c_str());
            EXPECT_NEAR(testOneFrame(image, *generateNextFrame()), 0.0, allowedRmsError);
        } catch(cimg_library::CImgException& e) {
            std::cout << "problems with loading the test frames or decoding the file" << std::endl;
            break;
        }
    }
}