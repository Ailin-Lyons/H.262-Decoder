//
// Created by bhave on 11/19/2019.
//

#include <stdio.h>
#include <iostream>
#include <string.h>
#include "PacketParsers/TSParser.cpp"

// SPEC - global constants
// DESIGN - use builtin math

const static double pi = 3.14159265359;
const static double e = 2.71828182845;

// TODO: Use namepsace std??



// TODO: open the file and throw respective errors and exceptions

/*
 * Input: fileName, path
 * Output: file* or memory map
 */

int openStream(char* fileName, char* path) {
    return -1; // TODO
}

/* TODO: display the information in part 1
 * DESIGN: returns an int or a metadata struct
 *         inputs
 *         display and parse separately
*/

/*
 * SPEC -
 *      input:
 *      output:
 *      errors:
 *
 */
int parseMetaData() {
    return -1; // TODO
}

int displayMetaData() {
    return -1; // TODO
}

int main(int argc, char** argv) {

    openStream(nullptr, nullptr); // stub
    char fileName[] = "..\\..\\test files\\testvideo_noaudio.ts";
    char* fn = fileName;
    TSParser::ParseFileIntoPackets(fn); // TODO remove this line | its just for testing
    // TODO: split the file into 3 parts



    // TODO: part2 and part 3??
}


