//
// Created by elnsa on 2020-02-13.
//

#include <PictureDecoder.h>
#include <VideoDecoder.h>
#include "MCompensator.h"
#include "../../VideoDecoder/VideoException.cpp"
#include "Framestores.h"

/**
 * Constructor
 * @param frameType: I-Picture, P-Picture or B-Picture
 * @param concealment_motion_vectors
 */
MCompensator::MCompensator(PictureHeaderPacket::picture_coding_types frameType, bool concealment_motion_vectors) {
    this->frameType = frameType;
    this->concealment_motion_vectors = concealment_motion_vectors;
    resetPMV(); // Initialize all predictors to 0
}

void MCompensator::performMComp(HPicture *picture) {
    switch (frameType) {
        case PictureHeaderPacket::picture_coding_types::intra_coded:
            setMacroblockAddresses(picture);
            Framestores::getInstance()->updateFramestores(picture);
            break;
        case PictureHeaderPacket::picture_coding_types::predictive_coded:
            performMcompPPicture(picture);
            Framestores::getInstance()->updateFramestores(picture);
            break;
        default:
            throw VideoException(
                    "MotionCompensator::performMComp: Picture type not supported\n");
    }
}

void MCompensator::performMcompPPicture(HPicture *picture) {
    addMissingMacroblocks(picture);
    setMacroblockAddresses(picture);
    for (size_t s = 0; s < picture->getNumSlices(); s++) {
        Slice *slice = picture->getSlices()[s];
        resetPMV(); //At the start of each slice H.262 7.6.3.4
        for (size_t m = 0; m < slice->getNumMacroblocks(); m++) {
            Macroblock *macroblock = slice->getMacroblocks()[m];
            if (macroblock->getMacroBlockModes()->getFrameMotionType() != 0b10) {
                throw VideoException("MCompensator::performMcompPPicture: Prediction type not handled by decoder.");
            }
            //This code only handles Frame pictures
            checkResetPMV(macroblock);
            if (!macroblock->getMacroBlockModes()->isMacroblockIntra()) performMCompMacroblock(macroblock);
        }
    }
}

void MCompensator::performMCompMacroblock(Macroblock *macroblock) {
    if (macroblock->getMacroblockAddressIncrement() != 0) {
        decodeMotionVectors(macroblock); // Decodes motion vectors according to H.262 7.6.3.1
        updateRemainingPredictors(macroblock); // Updates predictors according to H.262 7.6.3.3
        handleMissingPredictors(macroblock); // Makes missing vectors according to H.262 7.6.3.5
    }
    handlePredictions(macroblock);
}

/**
 * Decodes motion vectors according to H.262 7.6.3.1
 */
void MCompensator::decodeMotionVectors(Macroblock *macroblock) {
    if (macroblock->getForwardMotionVectors()) {
        MotionVector *mv0s = macroblock->getForwardMotionVectors()->getMotionVector0S();
        if (mv0s) decodeVectorPrime(mv0s);
        MotionVector *mv1s = macroblock->getForwardMotionVectors()->getMotionVector1S();
        if (mv1s) decodeVectorPrime(mv1s);
    }
    if (macroblock->getBackwardMotionVectors()) {
        MotionVector *bv0s = macroblock->getBackwardMotionVectors()->getMotionVector0S();
        if (bv0s) decodeVectorPrime(bv0s);
        MotionVector *bv1s = macroblock->getBackwardMotionVectors()->getMotionVector1S();
        if (bv1s) decodeVectorPrime(bv1s);
    }
}

void MCompensator::decodeVectorPrime(MotionVector *motionVector) {
    motionVector->setVectorRS0(decodeVectorPrimeHelper(motionVector->getMotionCodeRS0(),
                                                       motionVector->getMotionResidualRS0(),
                                                       motionVector->isR(),
                                                       motionVector->isS(),
                                                       0)); // NOLINT(modernize-use-bool-literals)
    motionVector->setVectorRS1(decodeVectorPrimeHelper(motionVector->getMotionCodeRS1(),
                                                       motionVector->getMotionResidualRS1(),
                                                       motionVector->isR(),
                                                       motionVector->isS(),
                                                       1)); // NOLINT(modernize-use-bool-literals)
}

int MCompensator::decodeVectorPrimeHelper(char motion_code, unsigned char residual, bool r, bool s, bool t) {
    int r_size = (int) (VideoDecoder::getInstance()->getPictureDecoder()->getFCodeST(s, t) - 1);
    int f = 1 << r_size; // NOLINT(hicpp-signed-bitwise)
    int high = (16 * f) - 1;
    int low = (-16 * f);
    int range = (32 * f);
    int delta;
    if ((f == 1) || (motion_code == 0)) delta = motion_code;
    else {
        delta = ((abs(motion_code) - 1) * f) + residual + 1;
        if (motion_code < 0) delta = -delta;
    }
    int prediction = PMV[r][s][t];
    /**
     * Field predictions are not handled by the decoder
     * if ( (mv_format == "field") && (t==1) && (picture_structure == "Frame picture") )
     *      prediction=PMV[s][t] DIV 2;
     */
    int out = prediction + delta;
    if (out < low) out += range;
    if (out > high) out -= range;
    /**
     * Field predictions are not handled by the decoder
     * if ((mv_format == "field") && (t == 1) && (picture_structure == "Frame picture"))
     *      PMV[r][s][t] = vector'[r][s][t] * 2;
     */
    PMV[r][s][t] = out;
    return out;
}

/**
 * Update remaining predictors according to H.262 7.6.3.3
 * This decoder does not handle field pictures
 * @param macroblock
 */
void MCompensator::updateRemainingPredictors(Macroblock *macroblock) {
    bool mmf = macroblock->getMacroBlockModes()->isMacroblockMotionForward();
    bool mmb = macroblock->getMacroBlockModes()->isMacroblockMotionBackward();
    if (macroblock->getMacroBlockModes()->isMacroblockIntra()) {
        PMV[1][0][0] = PMV[0][0][0];
        PMV[1][0][1] = PMV[0][0][1];
    } else {
        if (mmf) {
            PMV[1][0][0] = PMV[0][0][0];
            PMV[1][0][1] = PMV[0][0][1];
        }
        if (mmb) {
            PMV[1][1][0] = PMV[0][1][0];
            PMV[1][1][1] = PMV[0][1][1];
        }
    }
}

/**
 * Handles the case of missing predictors according to H.262 7.6.3.5
 */
void MCompensator::handleMissingPredictors(Macroblock *macroblock) {
    if (!macroblock->getMacroBlockModes()->isMacroblockMotionForward() &&
        !macroblock->getMacroBlockModes()->isMacroblockIntra()) {
        macroblock->getMacroBlockModes()->setFrameMotionType(0b10);
        macroblock->setForwardMotionVectors(MotionVectors::buildZeroVectors(0)); // NOLINT(modernize-use-bool-literals)
    }
}

/**
 * Decides whether to reset predictors according to H.262 7.6.3.4
 */
void MCompensator::checkResetPMV(Macroblock *macroblock) {
    bool intra = macroblock->getMacroBlockModes()->isMacroblockIntra();
    bool motion_forward = macroblock->getMacroBlockModes()->isMacroblockMotionForward();
    if ((intra && !concealment_motion_vectors) || //H.262 7.6.3.4
        (!intra && !motion_forward) ||
        (macroblock->getMacroblockAddressIncrement() > 1)) {
        resetPMV();
    }
}

/**
 * Helper for checkResetPMV that resets all predictors to 0
 */
void MCompensator::resetPMV() {
    for (size_t r = 0; r < 2; r++) { // NOLINT(modernize-loop-convert)
        for (size_t s = 0; s < 2; s++) {
            for (size_t t = 0; t < 2; t++) {
                PMV[r][s][t] = 0;
            }
        }
    }
}

void MCompensator::addMissingMacroblocks(HPicture *picture) {
    for (size_t s = 0; s < picture->getNumSlices(); s++) {
        Slice *slice = picture->getSlices()[s];
        for (size_t m = 0; m < slice->getNumMacroblocks(); m++) {
            Macroblock *mb = slice->getMacroblocks()[m];
            if (mb->getMacroblockAddressIncrement() > 1) {
                for (size_t i = mb->getMacroblockAddressIncrement(); i > 1; i--) {
                    slice->insertZeroVectorMacroblock(m);
                    m++;//increment past inserted macroblock
                }
            }
        }
    }
}

void MCompensator::setMacroblockAddresses(HPicture *picture) {
    size_t index = 0;
    for (size_t s = 0; s < picture->getNumSlices(); s++) {
        Slice *slice = picture->getSlices()[s];
        for (size_t m = 0; m < slice->getNumMacroblocks(); m++) {
            Macroblock *mb = slice->getMacroblocks()[m];
            mb->setMacroblockAddress(index);
            index++;
        }
    }
}

/**
 * This function forms and merges predictions from motion vectors for Frame-Pictures
 */
void MCompensator::handlePredictions(Macroblock *macroblock) {
    if (!macroblock->getMacroBlockModes()->isMacroblockIntra()) {//if(!intra)
        if (macroblock->getMacroBlockModes()->isMacroblockMotionBackward()) {
            throw VideoException(
                    "MCompensator::handlePredictions: backwards motion vectors not handled by this decoder\n");
        }
        Framestores *fs = Framestores::getInstance();
        Macroblock *prediction = fs->getPredictionXY(macroblock->getMacroblockAddress(),
                                                     macroblock->getForwardMotionVectors()->getMotionVector0S());
        combinePrediction(macroblock, prediction);
    }
}

/**
 * Merges Prediction and Coefficient data into macroblock according to H.262 7.6.8
 * and deletes prediction
 */
void MCompensator::combinePrediction(Macroblock *macroblock, Macroblock *prediction) {
    addMissingBlocks(macroblock);
    for (size_t b = 0; b < macroblock->getBlockCount(); b++) {
        if (prediction->getBlock(b)) {
            int *dest = macroblock->getBlock(b)->getData();
            int *source = prediction->getBlock(b)->getData();
            for (size_t i = 0; i < 64; i++) {
                dest[i] = source[i] + dest[i];
                if (dest[i] < 0) dest[i] = 0;
                if (dest[i] > 255) dest[i] = 255;
            }
        }
    }
}

void MCompensator::addMissingBlocks(Macroblock *macroblock) {
    if (!macroblock->getBlocks())
        macroblock->setBlocks((Block **) calloc(macroblock->getBlockCount(), sizeof(void *)));
    for (size_t b = 0; b < macroblock->getBlockCount(); b++) {
        if (!macroblock->getBlock(b)) {
            macroblock->getBlocks()[b] = new Block(Block::initializerStruct{b, Block::calculateCC(b)});
        }
        Block *block = macroblock->getBlock(b);
        if (!block->getData()) {
            block->setData((int *) calloc(64, sizeof(int)));
        }
    }
}
