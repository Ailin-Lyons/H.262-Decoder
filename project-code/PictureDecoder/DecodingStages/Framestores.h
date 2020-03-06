//
// Created by elnsa on 2020-03-01.
//

#ifndef PROJECT_CODE_FRAMESTORES_H
#define PROJECT_CODE_FRAMESTORES_H


#include <HPicture.h>

class Framestores {//TODO implement
private:
    static Framestores *instance;
    size_t x_res;
    size_t y_res;
    int* lum;
    int* cr;
    int* cb;

    /**
    * A private constructor for the singleton
    */
    Framestores();

    ~Framestores();

public:
    static Framestores *getInstance() {
        if (!instance) {
            instance = new Framestores();
        }
        return instance;
    }

    void updateFramestores(HPicture* p);

    Macroblock* getPredictionXY(MotionVector* mv);

    static size_t divTruncNeg(int top, int bottom);

    Block *predictLumBlock(size_t x, size_t y, bool half_x, bool half_y);

    Block *predictChromBlock(int *arr, size_t x, size_t y, bool half_x, bool half_y);

    void updateFramestoresMacroblock(size_t index, Macroblock *mb);
};


#endif //PROJECT_CODE_FRAMESTORES_H
