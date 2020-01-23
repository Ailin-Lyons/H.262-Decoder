//
// Created by elnsa on 2020-01-19.
//

#ifndef PROJECT_CODE_MOTIONVECTOR_H
#define PROJECT_CODE_MOTIONVECTOR_H


class MotionVector {
private:
    short motion_code_r_s_0;
    unsigned char motion_residual_r_s_0;
    char dmvector_0;
    short motion_code_r_s_1;
    unsigned char motion_residual_r_s_1;
    char dmvector_1;
public:
    struct initializerStruct {
        unsigned short motion_code_r_s_0;
        unsigned char motion_residual_r_s_0;
        unsigned char dmvector_0;
        unsigned short motion_code_r_s_1;
        unsigned char motion_residual_r_s_1;
        unsigned char dmvector_1;
    };

    MotionVector(initializerStruct init);

    ~MotionVector() = default;

    void print();

    bool operator==(const MotionVector &rhs) const;

    bool operator!=(const MotionVector &rhs) const;
};


#endif //PROJECT_CODE_MOTIONVECTOR_H
