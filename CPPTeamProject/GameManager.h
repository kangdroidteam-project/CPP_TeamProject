#pragma once
#include "GameUIManager.h"
#include "TetrisCore.h"
class GameManager {
private:
    GlobalVariant gv;
    GameUIManager gui;
    TetrisCore tc;
    int fake_y;
public:
    GameManager(): gv(), gui(gv), tc(gui, gv) {
    }
    void test();
    void play();
    void printThis();
};
