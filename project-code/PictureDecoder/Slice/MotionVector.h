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
    char motion_code_r_s_0{};
    unsigned char motion_residual_r_s_0{};
    char dmvector_0{};
    char motion_code_r_s_1{};
    unsigned char motion_residual_r_s_1{};
    char dmvector_1{};
    int vector_r_s_0{};
    int vector_r_s_1{};

    MotionVector(bool r, bool s);

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

    explicit MotionVector(initializerStruct init);

    ~MotionVector() = default;

    void print();

    bool operator==(const MotionVector &rhs) const;

    bool operator!=(const MotionVector &rhs) const;

    bool isR() const;

    bool isS() const;

    char getMotionCodeRS0() const;

    unsigned char getMotionResidualRS0() const;

    char getDmvector0() const;

    char getMotionCodeRS1() const;

    unsigned char getMotionResidualRS1() const;

    char getDmvector1() const;

    int getVectorRS0() const;

    void setVectorRS0(int vectorPrimeRS0);

    int getVectorRS1() const;

    void setVectorRS1(int vectorPrimeRS1);

    static MotionVector *buildZeroVector(bool r, bool s);
};


#endif //PROJECT_CODE_MOTIONVECTOR_H
