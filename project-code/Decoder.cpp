//
// Created by bhave on 11/19/2019.
//


#include <ctime>
#include "ESParser.cpp"
#include "VideoDecoder.h"


// note - global constants
// DESIGN - use builtin math


const static double e = 2.71828182845;


/* TODO: display the information in part 1
 * DESIGN: returns an int or a metadata struct
 *         inputs
 *         display and parse separately
*/

int main(int argc, char **argv) {
    clock_t t = clock();
    try {
        char relative_path[] = R"(../../testFiles/testvideo.ts)";
        char destination[] = R"(../../test output/)"; //TODO clear destination folder before running the program
        VideoDecoder *vDecoder = VideoDecoder::getInstance();
        vDecoder->decodeToFile(relative_path, destination);

    } catch (PacketException &e) {
        printf("Gracefully shutting down after %f seconds.\n%s", ((float) (clock() - t)) / CLOCKS_PER_SEC, e.what());
    } catch (VideoException &e) {
        printf("Gracefully shutting down after %f seconds.\n%s", ((float) (clock() - t)) / CLOCKS_PER_SEC, e.what());
    }
}


