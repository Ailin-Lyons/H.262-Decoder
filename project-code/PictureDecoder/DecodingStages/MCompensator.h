//
// Created by elnsa on 2020-02-13.
//

#ifndef PROJECT_CODE_MCOMPENSATOR_H
#define PROJECT_CODE_MCOMPENSATOR_H


#include <HPicture.h>
#include "../../StreamPackets/ESPackets/RegularStartCodes/PictureHeaderPacket.h"

class MCompensator {

    int PMV[2][2][2]; //PMV[r][s][t]
    PictureHeaderPacket::picture_coding_types frameType;
    bool concealment_motion_vectors;

public:
    void performMComp(HPicture *picture);

    void performMCompHelper(HPicture *picture);

    void mCompFrameHelper(Macroblock *macroblock);

    void resetPMV();

    MCompensator(PictureHeaderPacket::picture_coding_types frameType, bool concealment_motion_vectors);

    void decodeMotionVectors(Macroblock *macroblock);

    void decodeVectorPrime(MotionVector *motionVector);

    int decodeVectorPrimeHelper(char vectorCode, unsigned char residual, bool r, bool s, bool t);

    void updateRemainingPredictors(Macroblock *macroblock);

    void handleMissingPredictors(Macroblock *macroblock);

    void makeChrominanceVectors(Macroblock *macroblock);

    void makeChrominanceVectorsHelper(MotionVectors *motionVectors);
};


#endif //PROJECT_CODE_MCOMPENSATOR_H
