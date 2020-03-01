//
// Created by elnsa on 2020-02-13.
//

#include <PictureDecoder.h>
#include <VideoDecoder.h>
#include <VideoInformation.h>
#include "MCompensator.h"
#include "../../VideoDecoder/VideoException.cpp"

/**
 * TODO (remove these) Notes:
 * In  P-pictures  prediction  shall  be  made  from  the  most  recently  reconstructed  reference  frame.  This  is  illustrated  in  Figure 7-10.
 */

void MCompensator::performMComp(HPicture *picture) {
    switch (frameType) {
        case PictureHeaderPacket::picture_coding_types::intra_coded:
            printf("TODO MComp handle I-frame\n");
            //TODO handle I-frame: add to framestore + anything else?
            break;
        case PictureHeaderPacket::picture_coding_types::predictive_coded:
            performMCompHelper(picture);
            break;
        case PictureHeaderPacket::picture_coding_types::bidirectionally_predictive_coded:
            throw VideoException(
                    "MotionCompensator::performMComp: B-frames not handled by this decoder\n");
    }
}

void MCompensator::performMCompHelper(HPicture *picture) {
    for (size_t s = 0; s < picture->getNumSlices(); s++) {
        Slice *slice = picture->getSlices()[s];
        for (size_t m = 0; m < slice->getNumMacroblocks(); m++) {
            Macroblock *macroblock = &slice->getMacroblocks()[m];
            bool intra = macroblock->getMacroBlockModes()->isMacroblockIntra();
            bool motion_forward = macroblock->getMacroBlockModes()->isMacroblockMotionForward();
            if (m == 0 || (intra && !concealment_motion_vectors) || //H.262 7.6.3.4
                (!intra && !motion_forward) ||
                (macroblock->getMacroblockAddressIncrement() > 1)) {
                resetPMV();
            }
            if (macroblock->getMacroBlockModes()->getFrameMotionType() != 0b10) {
                throw VideoException("MCompensator::performMCompHelper: Prediction type not handled by decoder.");
            }
            mCompFrameHelper(macroblock);
            //TODO continue here once helper is done
        }
    }
}

void MCompensator::mCompFrameHelper(Macroblock *macroblock) {
    decodeMotionVectors(macroblock); // Decodes motion vectors according to H.262 7.6.3.1
    updateRemainingPredictors(macroblock); // Updates predictors according to H.262 7.6.3.3
    handleMissingPredictors(macroblock); // Makes missing vectors according to H.262 7.6.3.5
    makeChrominanceVectors(macroblock); // Builds chrominace vectors from luminance vectors according to H.262 7.6.3.7

    //TODO implement
    //TODO continue with 7.6.4 here
}

void MCompensator::resetPMV() {
    for (int r = 0; r < 2; r++) {
        for (int s = 0; s < 2; s++) {
            for (int t = 0; t < 2; t++) {
                PMV[r][s][t] = 0;
            }
        }
    }
}

MCompensator::MCompensator(PictureHeaderPacket::picture_coding_types frameType, bool concealment_motion_vectors) {
    this->frameType = frameType;
    this->concealment_motion_vectors = concealment_motion_vectors;
    resetPMV();
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
    if (macroblock->getForwardMotionVectors()) {
        MotionVector *bv0s = macroblock->getForwardMotionVectors()->getMotionVector0S();
        if (bv0s) decodeVectorPrime(bv0s);
        MotionVector *bv1s = macroblock->getForwardMotionVectors()->getMotionVector1S();
        if (bv1s) decodeVectorPrime(bv1s);
    }
}

void MCompensator::decodeVectorPrime(MotionVector *motionVector) {
    motionVector->setLumVectorRS0(decodeVectorPrimeHelper(motionVector->getMotionCodeRS0(),
                                                          motionVector->getMotionResidualRS0(),
                                                          motionVector->isR(),
                                                          motionVector->isS(),
                                                          0));
    motionVector->setLumVectorRS1(decodeVectorPrimeHelper(motionVector->getMotionCodeRS0(),
                                                          motionVector->getMotionResidualRS0(),
                                                          motionVector->isR(),
                                                          motionVector->isS(),
                                                          1));
}

int MCompensator::decodeVectorPrimeHelper(char vectorCode, unsigned char residual, bool r, bool s, bool t) {
    unsigned int r_size = VideoDecoder::getInstance()->getPictureDecoder()->getFCodeST(s, t) - 1;
    int f = 1 << r_size;
    int high = (16 * f) - 1;
    int low = ((-16) * f);
    int range = (32 * f);
    int delta;
    if ((f == 1) || (vectorCode == 0)) delta = vectorCode;
    else {
        delta = ((abs(vectorCode) - 1) * f) + residual + 1;
        if (vectorCode < 0) delta = -delta;
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
        if (!mmf && !mmb) {
            resetPMV();
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
        macroblock->setForwardMotionVectors(MotionVectors::buildZeroVectors(0));
        resetPMV();
    }
}

void MCompensator::makeChrominanceVectors(Macroblock *macroblock) {
    SequenceExtensionPacket::chroma_format_type chromaType = VideoInformation::getInstance()->getChromaFormat();
    switch (chromaType) {
        case SequenceExtensionPacket::chroma_format_type::cf_420:
            if (macroblock->getForwardMotionVectors())
                makeChrominanceVectorsHelper(macroblock->getForwardMotionVectors());
            if (macroblock->getBackwardMotionVectors())
                makeChrominanceVectorsHelper(macroblock->getBackwardMotionVectors());
            break;
        default:
            throw VideoException("MCompensator::makeChrominanceVectors: Unhandled chroma format.\n");
    }
}

/**
 * Initialize Chrominance Vectors according to H.262 7.6.3.7
 * @param motionVectors
 */
void MCompensator::makeChrominanceVectorsHelper(MotionVectors *motionVectors) {
    MotionVector *mv0s = motionVectors->getMotionVector0S();
    MotionVector *mv1s = motionVectors->getMotionVector1S();
    if (mv0s) {
        mv0s->setChromVectorRS0(mv0s->getLumVectorRS0() / 2);
        mv0s->setChromVectorRS1(mv0s->getLumVectorRS1() / 2);
    }
    if (mv1s) {
        mv1s->setChromVectorRS0(mv1s->getLumVectorRS0() / 2);
        mv1s->setChromVectorRS1(mv1s->getLumVectorRS1() / 2);
    }
}
