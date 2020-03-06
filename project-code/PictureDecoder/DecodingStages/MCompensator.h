//
// Created by elnsa on 2020-02-13.
//

#ifndef PROJECT_CODE_MCOMPENSATOR_H
#define PROJECT_CODE_MCOMPENSATOR_H


#include <HPicture.h>
#include "../../StreamPackets/ESPackets/RegularStartCodes/PictureHeaderPacket.h"

class MCompensator {

    int PMV[2][2][2]{}; //PMV[r][s][t]
    PictureHeaderPacket::picture_coding_types frameType;
    bool concealment_motion_vectors;

public:
    void performMComp(HPicture *picture);

    void performMcompPPicture(HPicture *picture);

    void performMCompMacroblock(Macroblock *macroblock);

    void resetPMV();

    MCompensator(PictureHeaderPacket::picture_coding_types frameType, bool concealment_motion_vectors);

    void decodeMotionVectors(Macroblock *macroblock);

    void decodeVectorPrime(MotionVector *motionVector);

    int decodeVectorPrimeHelper(char vectorCode, unsigned char residual, bool r, bool s, bool t);

    void updateRemainingPredictors(Macroblock *macroblock);

    static void handleMissingPredictors(Macroblock *macroblock);

    void makeChromVectors(Macroblock *macroblock);

    static void makeChromVectors420(MotionVectors *motionVectors);

    void checkResetPMV(Macroblock *macroblock);

    static void addMissingMacroblocks(HPicture *picture);

    /**
     * @requires there are no missing macroblocks in picture
     * Sets the macroblock_address field for all macroblocks in picture
     * @param picture
     */
    static void setMacroblockAddresses(HPicture *picture);

    void handlePredictions(Macroblock *macroblock);

    void combinePrediction(Macroblock *macroblock, Macroblock *prediction);

    static void addMissingBlocks(Macroblock *macroblock);
};


#endif //PROJECT_CODE_MCOMPENSATOR_H
