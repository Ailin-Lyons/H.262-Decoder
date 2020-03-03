//
// Created by elnsa on 2020-03-01.
//

#ifndef PROJECT_CODE_FRAMESTORES_H
#define PROJECT_CODE_FRAMESTORES_H


#include <HPicture.h>

class Framestores {//TODO implement
private:
    static Framestores *instance;
    HPicture picture;

    /**
    * A private constructor for the singleton
    */
    Framestores() = default;

public:
    static Framestores *getInstance() {
        if (!instance) {
            instance = new Framestores();
        }
        return instance;
    }

    void updateFramestores(HPicture p);

    Macroblock* getPredictionXY(MotionVector mv);
};


#endif //PROJECT_CODE_FRAMESTORES_H
