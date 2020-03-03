//
// Created by elnsa on 2020-03-01.
//

#include "Framestores.h"

void Framestores::updateFramestores(HPicture p) {
//TODO destroy old picture? refcount?
picture = p;
}

Macroblock *Framestores::getPredictionXY(MotionVector mv) {
    return nullptr; //TODO
}
