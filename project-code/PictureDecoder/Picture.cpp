//
// Created by elnsa on 2020-01-28.
//

#include "Picture.h"

Picture::Picture() {
    state = decoding_state::variable_length_decoded;
    numSlices = 0;
    //TODO continue initializing stuff
}

void Picture::addSlice(Slice *slice) {
    slice->print();//TODO add slice to slices
}

void Picture::performInverseScan() {
//TODO iterate over slices and perform inverse scan
}

void Picture::performInverseQuantisation() {
//TODO iterate over slices and perform inverse quantisation
}

void Picture::performDCT() {
//TODO iterate over slices and perform DCT
}
