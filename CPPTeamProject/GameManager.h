#pragma once
#include "GameUIManager.h"
#include "TetrisCore.h"
#include "BlockManager.h"
class GameManager {
private:
    GlobalVariant gv;
    BlockManager bm;
    GameUIManager gui;
    TetrisCore tc;
    int fake_y;
    int level;
public:
    GameManager() : gv(), bm(), gui(gv, bm), tc(gui, gv, bm) {
        gui.setCursorView(false);
        //level (0~4)
        //0 : 모스부호 
        //1 : 애니팡
        //2 : 모음
        //3 : 센트롬
        //4: 자음
        //5 : 보통게임

        this->level = 3;
    }
    void test();
    void play();
    void printThis();
};
