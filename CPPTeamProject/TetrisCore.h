#pragma once
#include "GlobalVariant.h"
#include "GameUIManager.h"
#include "StageInformation.h"
#include "BlockManager.h"

class TetrisCore {
private:
    GameUIManager &gui;
    GlobalVariant &gv;
    BlockManager &bm;
public:
    TetrisCore(GameUIManager& gameUI, GlobalVariant& glovalVar, BlockManager& blockMan);
    int make_new_block(const int& level);

    //Check wheter block is touching elswhere.
    //Returns 1 if they are touching anything, 0 when not.
    // INNER FUNCTION
    int strike_check(const int& level, const int& shape, const int& angle, int& x, const int& y, const int& isRot);

    // INNER FUNCTION
    int merge_block( const int& level, int& shape,   int& angle,   int& x,   int& y);

    // Set initial state for first-block start.
    int block_start(const int& level, int& angle, int& x, int& y);

    // INNER FUNCTION
    int check_full_line();
    int check_color( int x, int y,int& count, int k);

    int init();

    void colorpop();

    int move_block(const int& level, int& shape, int& angle, int& x, int& y, int& next_shape, const bool& isFake);

};

