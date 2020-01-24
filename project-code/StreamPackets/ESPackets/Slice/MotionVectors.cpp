//
// Created by elnsa on 2020-01-18.
//

#include <cstdio>
#include "MotionVectors.h"

MotionVectors::MotionVectors(MotionVectors::initializerStruct init) {
    this->motion_vertical_field_select_0_s = init.motion_vertical_field_select_0_s;
    this->motion_vector_0_s = init.motion_vector_0_s;
    this->motion_vector_1_s = init.motion_vector_1_s;
    this->motion_vertical_field_select_1_s = init.motion_vertical_field_select_1_s;
}

void MotionVectors::print() {
    std::printf("\tmotion_vertical_field_select_0_s = %s, motion_vertical_field_select_1_s = %s\n",
            motion_vertical_field_select_0_s ? "true" : "false", motion_vertical_field_select_1_s ? "true" : "false");
    if (motion_vector_0_s) {
        std::printf("\tMotion_Vector[0][s]");
        motion_vector_0_s->print();
    }
    if (motion_vector_1_s) {
        std::printf("\tMotion_Vector[1][s]");
        motion_vector_1_s->print();
    }
}

bool MotionVectors::operator==(const MotionVectors &rhs) const {
    return motion_vertical_field_select_1_s == rhs.motion_vertical_field_select_1_s &&
    motion_vertical_field_select_0_s == rhs.motion_vertical_field_select_0_s &&
    *motion_vector_0_s == *(rhs.motion_vector_0_s) && *motion_vector_1_s == *(rhs.motion_vector_1_s);
}

bool MotionVectors::operator!=(const MotionVectors &rhs) const {
    return !(rhs == *this);
}

MotionVectors::~MotionVectors() {
    delete motion_vector_1_s;
    delete motion_vector_0_s;
}
