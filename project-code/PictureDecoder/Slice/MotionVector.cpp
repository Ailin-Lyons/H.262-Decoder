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
    printf("mc_%x_%x_0 = %hhd, mc_%x_%x_1 = %hhd, dmv_0 = %c, dmv_1 = %c, mr_%x_%x_0 = %hhu, mr_%x_%x_1 = %hhu\n",
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

int MotionVector::getVectorRS0() const {
    return vector_r_s_0;
}

void MotionVector::setVectorRS0(int vectorPrimeRS0) {
    vector_r_s_0 = vectorPrimeRS0;
}

int MotionVector::getVectorRS1() const {
    return vector_r_s_1;
}

void MotionVector::setVectorRS1(int vectorPrimeRS1) {
    vector_r_s_1 = vectorPrimeRS1;
}

bool MotionVector::isR() const {
    return r;
}

bool MotionVector::isS() const {
    return s;
}

char MotionVector::getMotionCodeRS0() const {
    return motion_code_r_s_0;
}

unsigned char MotionVector::getMotionResidualRS0() const {
    return motion_residual_r_s_0;
}

char MotionVector::getDmvector0() const {
    return dmvector_0;
}

char MotionVector::getMotionCodeRS1() const {
    return motion_code_r_s_1;
}

unsigned char MotionVector::getMotionResidualRS1() const {
    return motion_residual_r_s_1;
}

char MotionVector::getDmvector1() const {
    return dmvector_1;
}

MotionVector *MotionVector::buildZeroVector(bool r, bool s) {
    return new MotionVector(r, s);
}

MotionVector::MotionVector(bool r, bool s) {
    this->r = r;
    this->s = s;
    vector_r_s_0 = 0;
    vector_r_s_1 = 0;
}
