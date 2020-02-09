//
// Created by bhave on 11/19/2019.
//


#include <ctime>
#include "ESParser.cpp"
#include "VideoDecoder.h"
#include "CImg283/CImg.h"


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
        char relative_path[] = R"(../../test files/testvideo_noaudio.ts)";
        char destination[] = R"(..\..\Images\)"; //TODO make a folder to save files
        VideoDecoder *vDecoder = VideoDecoder::getInstance();
        vDecoder->decodeToFile(relative_path, destination);

    } catch (PacketException &e) {
        printf("Gracefully shutting down after %f seconds.\n%s", ((float) (clock() - t)) / CLOCKS_PER_SEC, e.what());
    } catch (VideoException &e) {
        printf("Gracefully shutting down after %f seconds.\n%s", ((float) (clock() - t)) / CLOCKS_PER_SEC, e.what());
    }
//    cimg_library::CImg<int> img(640,400,1,1);         // Define a 640x400 color image with 8 bits per color component.
//    img.fill(0);                                  // Set pixel values to 0 (color : black)
//    int purple[] = { 100 };       // Define a purple color
//    img.draw_text(100,100,"Hello World",purple);  // Draw a purple "Hello world" at coordinates (100,100).
//    //img.display("Window Title");                  // Display the image in a display window.
//    img.save_png("0.png");                     // Save as PNG to prove we linked correctly
//    return 0;
}


