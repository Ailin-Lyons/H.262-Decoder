//
// Created by elnsa on 2020-03-01.
//

#include "Framestores.h"

Framestores *Framestores::instance = nullptr;

void Framestores::updateFramestores(HPicture *p) {
    delete picture;
    picture = p;
}

/**
 *
 * @param mv
 * @return a Macroblock or nullptr
 */
Macroblock *Framestores::getPredictionXY(MotionVector* mv) {
    return picture->getSlices()[0]->getMacroblocks()[0]; //TODO
}
