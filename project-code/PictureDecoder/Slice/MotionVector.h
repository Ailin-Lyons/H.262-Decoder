//
// Created by elnsa on 2020-01-19.
//

#ifndef PROJECT_CODE_MOTIONVECTOR_H
#define PROJECT_CODE_MOTIONVECTOR_H

/**
 * This class represents motion_vector ( r, s ) from H262 6.2.5.2.1
 */
class MotionVector {
private:
    bool r;
    bool s;
    char motion_code_r_s_0;
    unsigned char motion_residual_r_s_0;
    char dmvector_0;
    char motion_code_r_s_1;
    unsigned char motion_residual_r_s_1;
    char dmvector_1;
public:
    struct initializerStruct {
        bool r;
        bool s;
        char motion_code_r_s_0;
        unsigned char motion_residual_r_s_0;
        char dmvector_0;
        char motion_code_r_s_1;
        unsigned char motion_residual_r_s_1;
        char dmvector_1;
    };

    MotionVector(initializerStruct init);

    ~MotionVector() = default;

    void print();

    bool operator==(const MotionVector &rhs) const;

    bool operator!=(const MotionVector &rhs) const;
};


#endif //PROJECT_CODE_MOTIONVECTOR_H
