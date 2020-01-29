//
// Created by elnsa on 2020-01-19.
//

#include "MotionVector.h"

#include <cstdio>

MotionVector::MotionVector(MotionVector::initializerStruct init) {
    r = init.r;
    s = init.s;
    motion_code_r_s_0 = init.motion_code_r_s_0;
    motion_code_r_s_1 = init.motion_code_r_s_1;
    dmvector_0 = init.dmvector_0;
    dmvector_1 = init.dmvector_1;
    motion_residual_r_s_0 = init.motion_residual_r_s_0;
    motion_residual_r_s_1 = init.motion_residual_r_s_1;
}

void MotionVector::print() {
    printf("mc_%x_%x_0 = %c, mc_%x_%x_1 = %c, dmv_0 = %c, dmv_1 = %c, mr_%x_%x_0 = %hhu, mr_%x_%x_1 = %hhu\n",
           r, s, motion_code_r_s_0,
           r, s, motion_code_r_s_1,
           dmvector_0, dmvector_1,
           r, s, motion_residual_r_s_0,
           r, s, motion_residual_r_s_1);
}

bool MotionVector::operator==(const MotionVector &rhs) const {
    return r == rhs.r && s == rhs.s &&
           motion_residual_r_s_0 == rhs.motion_residual_r_s_0 &&
           motion_residual_r_s_1 == rhs.motion_residual_r_s_1 &&
           motion_code_r_s_1 == rhs.motion_code_r_s_1 &&
           motion_residual_r_s_0 == rhs.motion_code_r_s_0 &&
           dmvector_0 == rhs.dmvector_0 &&
           dmvector_1 == rhs.dmvector_1;
}

bool MotionVector::operator!=(const MotionVector &rhs) const {
    return !(rhs == *this);
}
