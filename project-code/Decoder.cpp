//
// Created by bhave on 11/19/2019.
//


#include "ESParser.cpp"


// note - global constants
// DESIGN - use builtin math

const static double pi = 3.14159265359;
const static double e = 2.71828182845;


/* TODO: display the information in part 1
 * DESIGN: returns an int or a metadata struct
 *         inputs
 *         display and parse separately
*/

/**
 * @return
 */
int parseMetaData() {
    return -1; // TODO
}

int displayMetaData() {
    return -1; // TODO
}

int main(int argc, char **argv) {
    char relative_path[] = R"(..\..\test files\testvideo_noaudio.ts)";
    char destination[] = R"(..\..\TODO\TODO\TODO)"; //TODO make a folder to save files
    VideoDecoder* vDecoder = VideoDecoder::getInstance();
    vDecoder->decodeToFile(relative_path,destination);
    // TODO: split the file into 3 parts



    // TODO: part2 and part 3??
}


