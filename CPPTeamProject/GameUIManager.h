#pragma once
#pragma warning(disable:4996)

#include "BlockManager.h"
#include "GlobalVariant.h"

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <iomanip>

using namespace std;

//class GameUIManager : public BlockManager {
class GameUIManager{
private:
    GlobalVariant& gv;
    BlockManager& bm;
public:
    GameUIManager(GlobalVariant& input,BlockManager& bm);


    int show_cur_block(const int& level, const int& shape, const int& angle, const int& x, const int& y, const bool& isFake);
    int erase_cur_block(const int& level, const int& shape, const int& angle, const int& x, const int& y, const bool& isFake);
    int show_total_block(const int& level);

    
    int show_next_block(const int& level,const int& shape);

    int show_logo();
    int show_gamestat();

    int show_gameover();

    int input_data();
    void SetColor(const int& color);
    int gotoxy(const int& x, const int& y);
    void setCursorView(bool visible);
};

