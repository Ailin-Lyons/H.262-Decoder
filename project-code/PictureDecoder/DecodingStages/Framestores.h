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
    int *lum;
    int *cb;
    int *cr;

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

    void updateFramestores(HPicture *p);

    Macroblock *getPredictionXY(int macroblock_index, MotionVector *mv);


    static Block *predictBlock(size_t block_index, const int *arr, size_t width, size_t height,
                               int x_base, int y_base, bool half_x, bool half_y);

    void updateFramestoresMacroblock(size_t index, Macroblock *mb);

    static void addBlock(int *targetArray, size_t width, size_t x_base, size_t y_base, Block *toAdd);

    static int div2TruncNeg(int numerator);

    static int div2Round(int numerator);

    static int div4Round(int numerator);
};


#endif //PROJECT_CODE_FRAMESTORES_H
