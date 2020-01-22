//
// Created by elnsa on 2020-01-18.
//

#include "MotionVectors.h"

MotionVectors::MotionVectors(MotionVectors::initializerStruct init) {
    this->motion_vertical_field_select_0_s = init.motion_vertical_field_select_0_s;
    this->motion_vector_0_s = init.motion_vector_0_s;
    this->motion_vector_1_s = init.motion_vector_1_s;
    this->motion_vertical_field_select_1_s = init.motion_vertical_field_select_1_s;
}

void MotionVectors::print() {
//TODO
}

bool MotionVectors::operator==(const MotionVectors &rhs) const {
    return false;//TODO
}

bool MotionVectors::operator!=(const MotionVectors &rhs) const {
    return !(rhs == *this);
}

MotionVectors::~MotionVectors() {
    delete motion_vector_1_s;
    delete motion_vector_0_s;
}
