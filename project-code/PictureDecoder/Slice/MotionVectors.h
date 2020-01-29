//
// Created by elnsa on 2020-01-18.
//

#ifndef PROJECT_CODE_MOTIONVECTORS_H
#define PROJECT_CODE_MOTIONVECTORS_H


#include "MotionVector.h"

/**
 * This class represents motion_vectors (s) from H262 6.2.5.2
 */
class MotionVectors {
private:
    bool s;
    bool motion_vertical_field_select_0_s;
    bool motion_vertical_field_select_1_s;
    MotionVector *motion_vector_0_s;
    MotionVector *motion_vector_1_s;
public:
    struct initializerStruct {
        bool s;
        bool motion_vertical_field_select_0_s;
        bool motion_vertical_field_select_1_s;
        MotionVector *motion_vector_0_s;
        MotionVector *motion_vector_1_s;
    };

    MotionVectors(initializerStruct init);

    ~MotionVectors();

    void print();

    bool operator==(const MotionVectors &rhs) const;

    bool operator!=(const MotionVectors &rhs) const;
};


#endif //PROJECT_CODE_MOTIONVECTORS_H
