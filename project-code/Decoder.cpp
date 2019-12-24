//
// Created by bhave on 11/19/2019.
//

#include <iostream>
#include <PESPacket.h>
#include "PacketParsers/TSParser.cpp"
#include "PacketParsers/PESParser.cpp"

// note - global constants
// DESIGN - use builtin math

const static double pi = 3.14159265359;
const static double e = 2.71828182845;

// TODO: Use namepsace std??



// TODO: open the file and throw respective errors and exceptions

/*
 * Input: fileName, path
 * Output: file* or memory map
 */

int openStream(char *file_name, char *path) {
    return -1; // TODO return appropriate ints depending on whether constructor was successful
}

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
    //char relative_path[] = "..\\..\\test files\\single_packet_hasAF.ts";
    char relative_path[] = R"(..\..\test files\testvideo_noaudio.ts)";
    char *path = relative_path;
    TSParser *tsParser = new TSParser(path);
    while (tsParser->HasNextPacket()) {
        TransportPacket* tp = tsParser->GetNextPacket();
        tp->toString();
        PESParser::pes_parser_struct pps = PESParser::parseTransportPacket(tp);
        for(int i = 0; i < pps.num_packets; i++){
            pps.packet_array[i].toString();
        }
    }
    // TODO: split the file into 3 parts



    // TODO: part2 and part 3??
}


