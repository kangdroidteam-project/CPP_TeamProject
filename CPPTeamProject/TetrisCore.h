#pragma once
#include "GlobalVariant.h"
#include "GameUIManager.h"
#include "StageInformation.h"

class TetrisCore {
private:
    GameUIManager &gui;
    GlobalVariant &gv;
public:
    TetrisCore(GameUIManager& gameUI, GlobalVariant& glovalVar);
    int make_new_block();

    //Check wheter block is touching elswhere.
    //Returns 1 if they are touching anything, 0 when not.
    // INNER FUNCTION
    int strike_check(int shape, int angle, int* x, int y, int isRot);

    // INNER FUNCTION
    int merge_block(int shape, int angle, int x, int y);

    // Set initial state for first-block start.
    int block_start(int* angle, int* x, int* y);

    // INNER FUNCTION
    int check_full_line();

    int init();

    int move_block(int* shape, int* angle, int* x, int* y, int* next_shape);
};

