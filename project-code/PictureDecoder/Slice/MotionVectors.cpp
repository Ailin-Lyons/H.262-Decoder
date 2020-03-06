//
// Created by elnsa on 2020-01-18.
//

#include <cstdio>
#include "MotionVectors.h"

MotionVectors::MotionVectors(MotionVectors::initializerStruct init) {
    s = init.s;
    motion_vertical_field_select_0_s = init.motion_vertical_field_select_0_s;
    motion_vector_0_s = init.motion_vector_0_s;
    motion_vector_1_s = init.motion_vector_1_s;
    motion_vertical_field_select_1_s = init.motion_vertical_field_select_1_s;
}

void MotionVectors::print() {
    std::printf("\tmotion_vertical_field_select_0_%x = %s, motion_vertical_field_select_1_%x = %s\n",
                s,
                motion_vertical_field_select_0_s ? "true" : "false",
                s,
                motion_vertical_field_select_1_s ? "true" : "false");
    if (motion_vector_0_s) {
        std::printf("\tMotion_Vector[0][%x]", s);
        motion_vector_0_s->print();
    }
    if (motion_vector_1_s) {
        std::printf("\tMotion_Vector[1][%x]", s);
        motion_vector_1_s->print();
    }
}

bool MotionVectors::operator==(const MotionVectors &rhs) const {
    return s == rhs.s &&
           motion_vertical_field_select_1_s == rhs.motion_vertical_field_select_1_s &&
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

bool MotionVectors::isS() const {
    return s;
}

bool MotionVectors::isMotionVerticalFieldSelect0S() const {
    return motion_vertical_field_select_0_s;
}

bool MotionVectors::isMotionVerticalFieldSelect1S() const {
    return motion_vertical_field_select_1_s;
}

MotionVector *MotionVectors::getMotionVector0S() const {
    return motion_vector_0_s;
}

void MotionVectors::setMotionVector0S(MotionVector *motionVector0S) {
    motion_vector_0_s = motionVector0S;
}

MotionVector *MotionVectors::getMotionVector1S() const {
    return motion_vector_1_s;
}

void MotionVectors::setMotionVector1S(MotionVector *motionVector1S) {
    motion_vector_1_s = motionVector1S;
}

MotionVectors *MotionVectors::buildZeroVectors(bool s) {
    MotionVectors::initializerStruct init = {s, 0,
                                             0,
                                             MotionVector::buildZeroVector(0, s)};
    return new MotionVectors(init);
}
