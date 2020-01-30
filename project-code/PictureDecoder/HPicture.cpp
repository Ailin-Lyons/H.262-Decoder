//
// Created by elnsa on 2020-01-28.
//

#include "HPicture.h"

HPicture::HPicture() {
    state = decoding_state::variable_length_decoded;
    numSlices = 0;
    //TODO continue initializing stuff
}

void HPicture::addSlice(Slice *slice) {
    slice->print();//TODO add slice to slices
}
